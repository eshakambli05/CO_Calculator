#ifndef COCALCULATOR_H
#define COCALCULATOR_H

#include <QVector>
#include <QMap>
#include "student.h"
#include "course.h"

class COCalculator {
public:
    static double calculateCOAttainment(const QVector<Student>& students, const Course& course, const QString& co, const QString& examType);
    static double calculateOverallCOAttainment(double isaAttainment, double seaAttainment);
};

#endif // COCALCULATOR_H
