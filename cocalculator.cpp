#include "cocalculator.h"

double COCalculator::calculateCOAttainment(const QVector<Student>& students, const Course& course, const QString& co, const QString& examType) {
    int totalStudents = students.size();
    int achieved = 0;
    for (const Student& student : students) {
        int totalMarks = 0;
        int maxMarks = 0;
        for (const Exam& exam : course.getExams()) {
            if (exam.getName().contains(examType)) {  // ISA or SEA
                totalMarks += student.getMarks(exam.getName(), co);
                maxMarks += exam.getCOMarks().value(co, 0);
            }
        }
        if (maxMarks > 0 && (static_cast<double>(totalMarks) / maxMarks) * 100 >= 60) {
            achieved++;
        }
    }
    double percentage = (static_cast<double>(achieved) / totalStudents) * 100;
    if (percentage >= 80) return 3;
    if (percentage >= 70) return 2;
    if (percentage >= 60) return 1;
    return 0;
}

double COCalculator::calculateOverallCOAttainment(double isaAttainment, double seaAttainment) {
    return 0.6 * isaAttainment + 0.4 * seaAttainment;
}
