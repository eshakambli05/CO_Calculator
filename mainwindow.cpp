#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "COCalculator.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentCourse(new Course())
    , m_currentFaculty(new Faculty())
    , m_reportGen(new ReportGenerator(this))
{
    ui->setupUi(this);

    // Initial Headers
    ui->tableCOs->setHorizontalHeaderLabels({"CO Code", "Description"});
    ui->tablePSOs->setHorizontalHeaderLabels({"PSO Code", "Description"});

    // --- Connections ---

    // Page 1: Setup
    connect(ui->btnGenCOs, &QPushButton::clicked, this, &MainWindow::generateCOTable);

    // Page 2: Mapping
    connect(ui->btnGenPSOs, &QPushButton::clicked, this, &MainWindow::generatePSOTable);
    connect(ui->btnGenMatrix, &QPushButton::clicked, this, &MainWindow::generateMatrixTable);

    // Page 4: Entry
    // Connect the "Reset/Create Table" button to FORCE creation
    connect(ui->btnGenEntryTable, &QPushButton::clicked, this, [=](){
        prepareEntryTable(true); // True = Force Reset
    });

    // Calculate & Export
    connect(ui->btnCalculate, &QPushButton::clicked, this, &MainWindow::calculateAndShowResults);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::exportPDF);

    // Navigation (Next)
    connect(ui->btnNext1, &QPushButton::clicked, this, [=](){ saveStep1Data(); nextPage(); });

    // Step 2 -> Step 3 (Max Marks): Ensure Max Marks table is prepared correctly
    connect(ui->btnNext2, &QPushButton::clicked, this, [=](){
        saveMappingData();
        prepareMaxMarksTable(); // CRITICAL: Creates editable items
        nextPage();
    });

    // Step 3 -> Step 4 (Entry): Ensure Entry table is prepared correctly
    connect(ui->btnNext3, &QPushButton::clicked, this, [=](){
        saveMaxMarksData();
        prepareEntryTable(true); // Force Reset to ensure editable cells exist
        nextPage();
    });

    // Navigation (Back)
    connect(ui->btnBack2, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnBack3, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnBack4, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnBack5, &QPushButton::clicked, this, &MainWindow::prevPage);

    // Styles
    ui->tableCOs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablePSOs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableMaxMarks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Start on Page 1
    ui->stackedWizard->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete m_currentCourse;
    delete m_currentFaculty;
    delete ui;
}

// Navigation
void MainWindow::nextPage() { ui->stackedWizard->setCurrentIndex(ui->stackedWizard->currentIndex() + 1); }
void MainWindow::prevPage() { ui->stackedWizard->setCurrentIndex(ui->stackedWizard->currentIndex() - 1); }

// --- STEP 1: Setup ---
void MainWindow::generateCOTable() {
    int count = ui->spinNumCOs->value();
    ui->tableCOs->setRowCount(count);
    for(int i=0; i<count; ++i) {
        ui->tableCOs->setItem(i, 0, new QTableWidgetItem(QString("CO%1").arg(i+1)));
        ui->tableCOs->setItem(i, 1, new QTableWidgetItem(""));
    }
}

void MainWindow::saveStep1Data() {
    m_currentFaculty->setName(ui->editFName->text());

    if(m_currentCourse) delete m_currentCourse;
    m_currentCourse = new Course(ui->editCourseCode->text(), ui->editCourseTitle->text());

    for(int i=0; i<ui->tableCOs->rowCount(); ++i) {
        QTableWidgetItem* itemCode = ui->tableCOs->item(i, 0);
        QTableWidgetItem* itemDesc = ui->tableCOs->item(i, 1);
        QString code = itemCode ? itemCode->text() : QString("CO%1").arg(i+1);
        QString desc = itemDesc ? itemDesc->text() : "";
        m_currentCourse->addCourseOutcome(CourseOutcome(code, desc));
    }
}

// --- STEP 2: PSO & Mapping ---
void MainWindow::generatePSOTable() {
    int count = ui->spinNumPSOs->value();
    ui->tablePSOs->setRowCount(count);
    for(int i=0; i<count; ++i) {
        ui->tablePSOs->setItem(i, 0, new QTableWidgetItem(QString("PSO%1").arg(i+1)));
        ui->tablePSOs->setItem(i, 1, new QTableWidgetItem(""));
    }
}

void MainWindow::generateMatrixTable() {
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();
    ui->tableMatrix->setRowCount(cos.size());
    QStringList rowLabels;
    for(const auto& co : cos) rowLabels << co.getCode();
    ui->tableMatrix->setVerticalHeaderLabels(rowLabels);

    int psoCount = ui->tablePSOs->rowCount();
    int colCount = 12 + psoCount;
    ui->tableMatrix->setColumnCount(colCount);

    QStringList colLabels;
    for(int i=1; i<=12; ++i) colLabels << QString("PO%1").arg(i);
    for(int i=0; i<psoCount; ++i) {
        QTableWidgetItem* item = ui->tablePSOs->item(i, 0);
        colLabels << (item ? item->text() : QString("PSO%1").arg(i+1));
    }
    ui->tableMatrix->setHorizontalHeaderLabels(colLabels);

    // Initialize with "0" to be editable
    for(int r=0; r<ui->tableMatrix->rowCount(); ++r) {
        for(int c=0; c<ui->tableMatrix->columnCount(); ++c) {
            QTableWidgetItem* item = new QTableWidgetItem("0");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableMatrix->setItem(r, c, item);
        }
    }
}

void MainWindow::saveMappingData() {
    m_currentCourse->clearPSOs();
    for(int i=0; i<ui->tablePSOs->rowCount(); ++i) {
        QTableWidgetItem* itemCode = ui->tablePSOs->item(i, 0);
        QTableWidgetItem* itemDesc = ui->tablePSOs->item(i, 1);
        QString code = itemCode ? itemCode->text() : QString("PSO%1").arg(i+1);
        QString desc = itemDesc ? itemDesc->text() : "";
        m_currentCourse->addPSO(code, desc);
    }

    for(int r=0; r<ui->tableMatrix->rowCount(); ++r) {
        QString coCode = ui->tableMatrix->verticalHeaderItem(r)->text();
        for(int c=0; c<ui->tableMatrix->columnCount(); ++c) {
            QString targetCode = ui->tableMatrix->horizontalHeaderItem(c)->text();
            QTableWidgetItem* item = ui->tableMatrix->item(r, c);
            int val = item ? item->text().toInt() : 0;
            m_currentCourse->setCorrelation(coCode, targetCode, val);
        }
    }
}

// --- STEP 3: Max Marks (FIXED: Explicit Editable Items) ---
void MainWindow::prepareMaxMarksTable() {
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();
    ui->tableMaxMarks->setRowCount(cos.size());
    QStringList rows; for(const auto& c : cos) rows << c.getCode();
    ui->tableMaxMarks->setVerticalHeaderLabels(rows);

    // IMPORTANT: Loop through and create items, otherwise they are NULL and uneditable
    for(int i=0; i<cos.size(); ++i) {
        // Column 0: ISA Max
        QTableWidgetItem* itemISA = new QTableWidgetItem("15");
        itemISA->setTextAlignment(Qt::AlignCenter);
        // Explicit flags just in case
        itemISA->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
        ui->tableMaxMarks->setItem(i, 0, itemISA);

        // Column 1: SEA Max
        QTableWidgetItem* itemSEA = new QTableWidgetItem("40");
        itemSEA->setTextAlignment(Qt::AlignCenter);
        itemSEA->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
        ui->tableMaxMarks->setItem(i, 1, itemSEA);
    }
}

void MainWindow::saveMaxMarksData() {
    for(int i=0; i<ui->tableMaxMarks->rowCount(); ++i) {
        QTableWidgetItem* itemISA = ui->tableMaxMarks->item(i, 0);
        QTableWidgetItem* itemSEA = ui->tableMaxMarks->item(i, 1);

        double isaMax = itemISA ? itemISA->text().toDouble() : 0.0;
        double seaMax = itemSEA ? itemSEA->text().toDouble() : 0.0;

        m_currentCourse->setMaxISAMarks(i, isaMax);
        m_currentCourse->setMaxSEAMarks(i, seaMax);
    }
}

// --- STEP 4: Entry (ROBUST FIX) ---
void MainWindow::prepareEntryTable(bool forceReset) {
    // 1. Validation
    if(m_currentCourse->getCourseOutcomes().isEmpty()) {
        QMessageBox::warning(this, "Setup Error", "No Course Outcomes (COs) defined.\nPlease go back to Step 1 and click 'Set COs'.");
        return;
    }

    // 2. Check if table is already populated (unless forcing reset)
    if (!forceReset && ui->tableEntry->rowCount() > 0) {
        return;
    }

    int numStudents = ui->spinNumStudents->value();
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();

    // 3. Clean Slate
    ui->tableEntry->blockSignals(true);
    ui->tableEntry->clear();

    // 4. Configure Properties to Ensure Editing
    ui->tableEntry->setRowCount(numStudents);
    int colCount = 2 + (cos.size() * 2);
    ui->tableEntry->setColumnCount(colCount);

    // Explicitly set interaction triggers in code as a backup to UI file
    ui->tableEntry->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tableEntry->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableEntry->setFocusPolicy(Qt::StrongFocus);

    // 5. Headers
    QStringList headers;
    headers << "Student Name" << "Roll No";
    for(const auto& co : cos) {
        headers << co.getCode() + " (ISA)" << co.getCode() + " (SEA)";
    }
    ui->tableEntry->setHorizontalHeaderLabels(headers);

    // 6. Populate EVERY cell with a valid item
    for(int i=0; i<numStudents; ++i) {
        for(int j=0; j<colCount; ++j) {
            // Create a non-null item
            QTableWidgetItem* item = new QTableWidgetItem("");

            // Enable editing flags explicitly
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            item->setTextAlignment(Qt::AlignCenter);

            ui->tableEntry->setItem(i, j, item);
        }
    }

    ui->tableEntry->blockSignals(false);
}

void MainWindow::readStudentData() {
    m_currentCourse->clearStudents();
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();
    int numStudents = ui->tableEntry->rowCount();

    bool foundData = false;

    for(int i=0; i<numStudents; ++i) {
        QTableWidgetItem* nameItem = ui->tableEntry->item(i, 0);
        QTableWidgetItem* rollItem = ui->tableEntry->item(i, 1);

        QString name = nameItem ? nameItem->text().trimmed() : "";
        QString roll = rollItem ? rollItem->text().trimmed() : "";

        // Handle empty names (Auto-generate if marks exist)
        if(name.isEmpty()) {
            bool hasMarks = false;
            int colMax = 2 + (cos.size() * 2);
            for(int k=2; k<colMax; k++) {
                if(ui->tableEntry->item(i, k) && !ui->tableEntry->item(i, k)->text().isEmpty()) {
                    hasMarks = true; break;
                }
            }
            if(!hasMarks) continue;
            name = QString("Student %1").arg(i+1);
        }

        Student s(name, roll);
        int colIdx = 2;
        for(int c=0; c<cos.size(); ++c) {
            double isaMark = (ui->tableEntry->item(i, colIdx)) ? ui->tableEntry->item(i, colIdx)->text().toDouble() : 0.0;
            double seaMark = (ui->tableEntry->item(i, colIdx+1)) ? ui->tableEntry->item(i, colIdx+1)->text().toDouble() : 0.0;
            s.setISAMark(c, isaMark);
            s.setSEAMark(c, seaMark);
            colIdx += 2;
        }
        m_currentCourse->addStudent(s);
        foundData = true;
    }

    if (!foundData) {
        QMessageBox::warning(this, "Input Warning", "No valid student data found.\nPlease enter at least a Name or Marks.");
    }
}

// --- STEP 5: Results & Final PO Calculation ---
void MainWindow::calculateAndShowResults() {
    readStudentData();

    if(m_currentCourse->getStudents().isEmpty()) return;

    nextPage();

    QList<Student> students = m_currentCourse->getStudents();
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();

    ui->tableResultISA->setRowCount(students.size());
    ui->tableResultISA->setColumnCount(2 + cos.size());
    ui->tableResultSEA->setRowCount(students.size());
    ui->tableResultSEA->setColumnCount(2 + cos.size());

    QStringList headers;
    headers << "Name" << "Roll No";
    for(const auto& co : cos) headers << co.getCode() + " Result";
    ui->tableResultISA->setHorizontalHeaderLabels(headers);
    ui->tableResultSEA->setHorizontalHeaderLabels(headers);

    // 1. Calculate Student Levels & CO Averages
    std::vector<double> finalCOAttainments(cos.size(), 0.0);
    std::vector<double> coLevelSums(cos.size(), 0.0);
    std::vector<int> coCounts(cos.size(), 0);

    for(int i=0; i<students.size(); ++i) {
        const Student& s = students[i];

        ui->tableResultISA->setItem(i, 0, new QTableWidgetItem(s.getName()));
        ui->tableResultISA->setItem(i, 1, new QTableWidgetItem(s.getRollNo()));
        ui->tableResultSEA->setItem(i, 0, new QTableWidgetItem(s.getName()));
        ui->tableResultSEA->setItem(i, 1, new QTableWidgetItem(s.getRollNo()));

        for(int c=0; c<cos.size(); ++c) {
            // ISA
            double isaMax = m_currentCourse->getMaxISAMarks(c);
            auto isaRes = COCalculator::calculateMetric(s.getISAMark(c), isaMax);
            QTableWidgetItem* itemISA = new QTableWidgetItem(QString("L%1 (%2%)").arg(isaRes.second).arg(isaRes.first, 0, 'f', 0));
            itemISA->setBackground(getLevelColor(isaRes.second));
            itemISA->setTextAlignment(Qt::AlignCenter);
            ui->tableResultISA->setItem(i, 2+c, itemISA);

            // SEA
            double seaMax = m_currentCourse->getMaxSEAMarks(c);
            auto seaRes = COCalculator::calculateMetric(s.getSEAMark(c), seaMax);
            QTableWidgetItem* itemSEA = new QTableWidgetItem(QString("L%1 (%2%)").arg(seaRes.second).arg(seaRes.first, 0, 'f', 0));
            itemSEA->setBackground(getLevelColor(seaRes.second));
            itemSEA->setTextAlignment(Qt::AlignCenter);
            ui->tableResultSEA->setItem(i, 2+c, itemSEA);

            // Accumulate for Average Calculation
            double avgStudentLevel = (isaRes.second + seaRes.second) / 2.0;
            coLevelSums[c] += avgStudentLevel;
            coCounts[c]++;
        }
    }
    ui->tableResultISA->resizeRowsToContents();
    ui->tableResultSEA->resizeRowsToContents();

    // 2. Compute Final CO Averages
    for(int c=0; c<cos.size(); ++c) {
        if(coCounts[c] > 0) {
            finalCOAttainments[c] = coLevelSums[c] / coCounts[c];
        }
    }

    // 3. Calculate Final PO Attainment (Popup)
    QString summary = "Final Attainment Calculation:\n\n";

    // POs
    for(int i=1; i<=12; ++i) {
        QString po = QString("PO%1").arg(i);
        std::vector<int> maps;
        for(const auto& co : cos) {
            maps.push_back(m_currentCourse->getCorrelation(co.getCode(), po));
        }

        double val = COCalculator::calculatePOAttainment(finalCOAttainments, maps);
        if(val > 0.01) summary += QString("%1: %2\n").arg(po).arg(val, 0, 'f', 2);
    }

    // PSOs
    QList<PSO> psos = m_currentCourse->getPSOs();
    for(const auto& pso : psos) {
        std::vector<int> maps;
        for(const auto& co : cos) {
            maps.push_back(m_currentCourse->getCorrelation(co.getCode(), pso.code));
        }

        double val = COCalculator::calculatePOAttainment(finalCOAttainments, maps);
        if(val > 0.01) summary += QString("%1: %2\n").arg(pso.code).arg(val, 0, 'f', 2);
    }

    QMessageBox::information(this, "Results Calculated", summary);
}

QColor MainWindow::getLevelColor(int level) {
    switch(level) {
    case 3: return QColor(144, 238, 144);
    case 2: return QColor(255, 255, 224);
    case 1: return QColor(255, 200, 150);
    default: return QColor(255, 182, 193);
    }
}

void MainWindow::exportPDF() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Report", "", "PDF Files (*.pdf)");
    if(filePath.isEmpty()) return;
    if (QFileInfo(filePath).suffix().isEmpty()) filePath.append(".pdf");

    if(m_reportGen->generatePDF(filePath, m_currentCourse, m_currentFaculty)) {
        QMessageBox::information(this, "Success", "Report exported!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to generate PDF.");
    }
}


