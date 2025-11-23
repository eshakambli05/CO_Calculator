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

    // Initial CO Table Setup
    ui->tableCOs->setHorizontalHeaderLabels({"CO Code", "Description"});

    // --- Connections ---

    // Buttons
    connect(ui->btnGenCOs, &QPushButton::clicked, this, &MainWindow::generateCOTable);
    connect(ui->btnGenEntryTable, &QPushButton::clicked, this, &MainWindow::prepareEntryTable);
    connect(ui->btnCalculate, &QPushButton::clicked, this, &MainWindow::calculateAndShowResults);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::exportPDF);

    // Navigation (Next Buttons)
    connect(ui->btnNext1, &QPushButton::clicked, this, [=](){
        saveStep1Data();
        prepareMaxMarksTable();
        nextPage();
    });

    connect(ui->btnNext2, &QPushButton::clicked, this, [=](){
        saveMaxMarksData();
        nextPage();
    });

    // Navigation (Back Buttons)
    connect(ui->btnBack2, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnBack3, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnBack4, &QPushButton::clicked, this, &MainWindow::prevPage);

    // Styles for tables (Better UI experience)
    ui->tableCOs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableMaxMarks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete m_currentCourse;
    delete m_currentFaculty;
    delete ui;
}

// --- Navigation Helpers ---

void MainWindow::nextPage() {
    int current = ui->stackedWizard->currentIndex();
    if (current < ui->stackedWizard->count() - 1) {
        ui->stackedWizard->setCurrentIndex(current + 1);
    }
}

void MainWindow::prevPage() {
    int current = ui->stackedWizard->currentIndex();
    if (current > 0) {
        ui->stackedWizard->setCurrentIndex(current - 1);
    }
}

// --- STEP 1: Faculty & CO Definitions ---

void MainWindow::generateCOTable() {
    int count = ui->spinNumCOs->value();
    ui->tableCOs->setRowCount(count);
    for(int i=0; i<count; ++i) {
        // Pre-fill CO Code (CO1, CO2, etc.)
        ui->tableCOs->setItem(i, 0, new QTableWidgetItem(QString("CO%1").arg(i+1)));
        // Empty Description
        ui->tableCOs->setItem(i, 1, new QTableWidgetItem(""));
    }
}

void MainWindow::saveStep1Data() {
    m_currentFaculty->setName(ui->editFName->text());

    // Re-initialize course with new data
    // Note: In a production app, you might want to update instead of replace to keep pointers valid
    // For this wizard flow, replacing ensures clean state.
    if(m_currentCourse) delete m_currentCourse;
    m_currentCourse = new Course(ui->editCourseCode->text(), ui->editCourseTitle->text());

    for(int i=0; i<ui->tableCOs->rowCount(); ++i) {
        QString code = ui->tableCOs->item(i, 0)->text();
        QString desc = ui->tableCOs->item(i, 1) ? ui->tableCOs->item(i, 1)->text() : "";
        m_currentCourse->addCourseOutcome(CourseOutcome(code, desc));
    }
}

// --- STEP 2: Max Marks Configuration ---

void MainWindow::prepareMaxMarksTable() {
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();
    ui->tableMaxMarks->setRowCount(cos.size());

    QStringList vLabels;
    for(const auto& co : cos) vLabels << co.getCode();
    ui->tableMaxMarks->setVerticalHeaderLabels(vLabels);

    // Default values (User can edit these)
    for(int i=0; i<cos.size(); ++i) {
        ui->tableMaxMarks->setItem(i, 0, new QTableWidgetItem("15")); // Default ISA Max
        ui->tableMaxMarks->setItem(i, 1, new QTableWidgetItem("40")); // Default SEA Max
    }
}

void MainWindow::saveMaxMarksData() {
    for(int i=0; i<ui->tableMaxMarks->rowCount(); ++i) {
        double isaMax = ui->tableMaxMarks->item(i, 0)->text().toDouble();
        double seaMax = ui->tableMaxMarks->item(i, 1)->text().toDouble();
        m_currentCourse->setMaxISAMarks(i, isaMax);
        m_currentCourse->setMaxSEAMarks(i, seaMax);
    }
}

// --- STEP 3: Student Data Entry ---

void MainWindow::prepareEntryTable() {
    int numStudents = ui->spinNumStudents->value();
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();

    ui->tableEntry->setRowCount(numStudents);

    // Calculate columns: Name + Roll + (ISA + SEA for each CO)
    int colCount = 2 + (cos.size() * 2);
    ui->tableEntry->setColumnCount(colCount);

    QStringList headers;
    headers << "Student Name" << "Roll No";
    for(const auto& co : cos) {
        headers << co.getCode() + " (ISA)" << co.getCode() + " (SEA)";
    }
    ui->tableEntry->setHorizontalHeaderLabels(headers);

    // Initialize empty cells to prevent null pointer crashes if read immediately
    for(int i=0; i<numStudents; ++i) {
        for(int j=0; j<colCount; ++j) {
            ui->tableEntry->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}

void MainWindow::readStudentData() {
    m_currentCourse->clearStudents();
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();
    int numStudents = ui->tableEntry->rowCount();

    for(int i=0; i<numStudents; ++i) {
        // Read Name and Roll
        QTableWidgetItem* nameItem = ui->tableEntry->item(i, 0);
        QTableWidgetItem* rollItem = ui->tableEntry->item(i, 1);

        QString name = nameItem ? nameItem->text() : "";
        QString roll = rollItem ? rollItem->text() : "";

        if(name.isEmpty()) continue; // Skip empty rows

        Student s(name, roll);

        // Read Marks Columns (Start index 2)
        int colIdx = 2;
        for(int c=0; c<cos.size(); ++c) {
            QTableWidgetItem* isaItem = ui->tableEntry->item(i, colIdx);
            QTableWidgetItem* seaItem = ui->tableEntry->item(i, colIdx+1);

            double isaMark = isaItem ? isaItem->text().toDouble() : 0.0;
            double seaMark = seaItem ? seaItem->text().toDouble() : 0.0;

            s.setISAMark(c, isaMark);
            s.setSEAMark(c, seaMark);

            colIdx += 2;
        }
        m_currentCourse->addStudent(s);
    }
}

// --- STEP 4: Results & Calculation ---

void MainWindow::calculateAndShowResults() {
    // 1. Read data from Entry Table
    readStudentData();

    // 2. Move to Results Page
    nextPage();

    QList<Student> students = m_currentCourse->getStudents();
    QList<CourseOutcome> cos = m_currentCourse->getCourseOutcomes();

    // 3. Configure Result Tables Structure
    ui->tableResultISA->setRowCount(students.size());
    ui->tableResultISA->setColumnCount(2 + cos.size());

    ui->tableResultSEA->setRowCount(students.size());
    ui->tableResultSEA->setColumnCount(2 + cos.size());

    QStringList headers;
    headers << "Name" << "Roll No";
    for(const auto& co : cos) headers << co.getCode() + " Result";

    ui->tableResultISA->setHorizontalHeaderLabels(headers);
    ui->tableResultSEA->setHorizontalHeaderLabels(headers);

    // 4. Perform Calculation and Fill Tables
    for(int i=0; i<students.size(); ++i) {
        const Student& s = students[i];

        // Fill Basic Info (ISA Table)
        ui->tableResultISA->setItem(i, 0, new QTableWidgetItem(s.getName()));
        ui->tableResultISA->setItem(i, 1, new QTableWidgetItem(s.getRollNo()));

        // Fill Basic Info (SEA Table)
        ui->tableResultSEA->setItem(i, 0, new QTableWidgetItem(s.getName()));
        ui->tableResultSEA->setItem(i, 1, new QTableWidgetItem(s.getRollNo()));

        // Calculate and Fill Marks
        for(int c=0; c<cos.size(); ++c) {

            // --- ISA Calculation ---
            double isaMax = m_currentCourse->getMaxISAMarks(c);
            auto isaRes = COCalculator::calculateMetric(s.getISAMark(c), isaMax);

            // Text: L{Level} ({Percentage}%)
            QString isaText = QString("L%1\n(%2%)").arg(isaRes.second).arg(isaRes.first, 0, 'f', 1);

            QTableWidgetItem* itemISA = new QTableWidgetItem(isaText);
            itemISA->setBackground(getLevelColor(isaRes.second));
            itemISA->setTextAlignment(Qt::AlignCenter);
            ui->tableResultISA->setItem(i, 2+c, itemISA);

            // --- SEA Calculation ---
            double seaMax = m_currentCourse->getMaxSEAMarks(c);
            auto seaRes = COCalculator::calculateMetric(s.getSEAMark(c), seaMax);

            // Text: L{Level} ({Percentage}%)
            QString seaText = QString("L%1\n(%2%)").arg(seaRes.second).arg(seaRes.first, 0, 'f', 1);

            QTableWidgetItem* itemSEA = new QTableWidgetItem(seaText);
            itemSEA->setBackground(getLevelColor(seaRes.second));
            itemSEA->setTextAlignment(Qt::AlignCenter);
            ui->tableResultSEA->setItem(i, 2+c, itemSEA);
        }
    }

    // 5. Resize rows to fit the multi-line text (L3 + Percentage)
    ui->tableResultISA->resizeRowsToContents();
    ui->tableResultSEA->resizeRowsToContents();
}

QColor MainWindow::getLevelColor(int level) {
    switch(level) {
    case 3: return QColor(144, 238, 144); // Light Green (Target Achieved High)
    case 2: return QColor(255, 255, 224); // Light Yellow (Moderate)
    case 1: return QColor(255, 200, 150); // Orange (Low)
    default: return QColor(255, 182, 193); // Light Red (Not Attained)
    }
}

// --- Export ---

void MainWindow::exportPDF() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Report", "", "PDF Files (*.pdf)");
    if(filePath.isEmpty()) return;

    // Add extension if missing
    if (QFileInfo(filePath).suffix().isEmpty()) {
        filePath.append(".pdf");
    }

    // Call ReportGenerator
    if(m_reportGen->generatePDF(filePath, m_currentCourse, m_currentFaculty)) {
        QMessageBox::information(this, "Success", "Report exported successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to generate PDF report.");
    }
}

