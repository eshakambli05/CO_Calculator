#include "reportgenerator.h"
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QPrinter>
#include <QTextDocument>

QString ReportGenerator::generateStudentMarksTable(const QVector<Student>& students, const Course& course) {
    QString table = "Student-wise CO Marks\nRoll No,Name,";
    for (const CourseOutcome& co : course.getCOs()) {
        table += co.getCode() + ",";
    }
    table += "\n";
    for (const Student& student : students) {
        table += student.getRollNo() + "," + student.getName() + ",";
        for (const CourseOutcome& co : course.getCOs()) {
            int total = 0;
            for (const Exam& exam : course.getExams()) {
                total += student.getMarks(exam.getName(), co.getCode());
            }
            table += QString::number(total) + ",";
        }
        table += "\n";
    }
    return table;
}

QString ReportGenerator::generateCOAttainmentTable(const QVector<Student>& students, const Course& course) {
    QString table = "CO Attainment\nCO,ISA Attainment,SEA Attainment,Overall Attainment\n";
    for (const CourseOutcome& co : course.getCOs()) {
        double isa = COCalculator::calculateCOAttainment(students, course, co.getCode(), "ISA");
        double sea = COCalculator::calculateCOAttainment(students, course, co.getCode(), "SEA");
        double overall = COCalculator::calculateOverallCOAttainment(isa, sea);
        table += co.getCode() + "," + QString::number(isa) + "," + QString::number(sea) + "," + QString::number(overall) + "\n";
    }
    return table;
}

QString ReportGenerator::generateCOPOMatrix(const Course& course) {
    QString table = "CO vs PO Matrix\nCO,";
    for (const QString& po : ProgramOutcome::getPredefinedPOs()) {
        table += po.split(":")[0] + ",";
    }
    table += "\n";
    for (const CourseOutcome& co : course.getCOs()) {
        table += co.getCode() + ",";
        for (const QString& po : ProgramOutcome::getPredefinedPOs()) {
            table += QString::number(co.getPOMapping().value(po.split(":")[0], 0)) + ",";
        }
        table += "\n";
    }
    return table;
}

QString ReportGenerator::generateCOPSOMatrix(const Course& course, const QVector<ProgramSpecificOutcome>& psos) {
    QString table = "CO vs PSO Matrix\nCO,";
    for (const ProgramSpecificOutcome& pso : psos) {
        table += pso.getCode() + ",";
    }
    table += "\n";
    for (const CourseOutcome& co : course.getCOs()) {
        table += co.getCode() + ",";
        for (const ProgramSpecificOutcome& pso : psos) {
            table += QString::number(co.getPSOMapping().value(pso.getCode(), 0)) + ",";
        }
        table += "\n";
    }
    return table;
}

QString ReportGenerator::generateFinalReport(const QVector<Student>& students, const Course& course, const QVector<ProgramSpecificOutcome>& psos) {
    return generateStudentMarksTable(students, course) + "\n\n" +
           generateCOAttainmentTable(students, course) + "\n\n" +
           generateCOPOMatrix(course) + "\n\n" +
           generateCOPSOMatrix(course, psos);
}

void ReportGenerator::exportToCSV(const QString& data, const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << data;
        file.close();
    }
}

void ReportGenerator::exportToPDF(const QString& data, const QString& filename) {
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    QTextDocument doc;
    doc.setPlainText(data);
    doc.print(&printer);
}
