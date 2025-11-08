#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QInputDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QVector>
#include "faculty.h"
#include "course.h"
#include "student.h"
#include "programspecificoutcome.h"
// #include <QSqlDatabase>  // For SQLite

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startWorkflow();
    void createCourse();
    void enterCOs();
    void mapPOs();
    void enterPSOs();
    void mapPSOs();
    void enterExams();
    void enterStudents();
    void enterMarks();
    void generateReports();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QLabel *statusLabel;
    QPushButton *nextButton;

    Faculty faculty;
    Course course;
    QVector<Student> students;
    QVector<ProgramSpecificOutcome> psos;
    int currentStep;

    void setupUI();
    void
