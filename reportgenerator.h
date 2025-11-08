#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QString>
#include <QVector>
#include <QMap>
#include "student.h"
#include "course.h"
#include "programspecificoutcome.h"

class ReportGenerator {
public:
    static QString generateStudentMarksTable(const QVector<Student>& students, const Course& course);
    static QString generateCOAttainmentTable(const QVector<Student>& students, const Course& course);
    static QString generateCOPOMatrix(const Course& course);
    static QString generateCOPSOMatrix(const Course& course, const QVector<ProgramSpecificOutcome>& psos);
    static QString generateFinalReport(const QVector<Student>& students, const Course& course, const QVector<ProgramSpecificOutcome>& psos);
    static void exportToCSV(const QString& data, const QString& filename);
    static void exportToPDF(const QString& data, const QString& filename);
};

#endif // REPORTGENERATOR_H
