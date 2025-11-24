#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QColor>
#include "Course.h"
#include "Faculty.h"
#include "ReportGenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation
    void nextPage();
    void prevPage();

    // Step 1: Setup
    void generateCOTable();

    // Step 2: Mapping (NEW)
    void generatePSOTable();
    void generateMatrixTable();

    // Step 3: Max Marks
    void prepareMaxMarksTable();

    // Step 4: Entry
    // No longer a slot because we call it via lambda or internal logic
    // void prepareEntryTable();

    // Step 5: Calculation & Export
    void calculateAndShowResults();
    void exportPDF();

private:
    Ui::MainWindow *ui;
    Course *m_currentCourse;
    Faculty *m_currentFaculty;
    ReportGenerator *m_reportGen;

    void saveStep1Data();
    void saveMappingData(); // NEW
    void saveMaxMarksData();

    // Helper function for table generation
    void prepareEntryTable(bool forceReset = false);

    void readStudentData();
    QColor getLevelColor(int level);
};
#endif // MAINWINDOW_H

