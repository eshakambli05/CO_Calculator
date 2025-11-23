#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
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

    // Setup Actions
    void generateCOTable();
    void prepareMaxMarksTable();
    void prepareEntryTable();

    // Calculation
    void calculateAndShowResults();
    void exportPDF();

private:
    Ui::MainWindow *ui;
    Course *m_currentCourse;
    Faculty *m_currentFaculty;
    ReportGenerator *m_reportGen;

    // Helper functions
    void saveStep1Data();
    void saveMaxMarksData();
    void readStudentData();

    // Attainment Logic
    int calculateLevel(double obtained, double max);
    QColor getLevelColor(int level);
};
#endif // MAINWINDOW_H
