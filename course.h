#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QVector>
#include "courseoutcome.h"
#include "exam.h"

class Course {
public:
    Course(const QString& code, const QString& title);
    QString getCode() const;
    QString getTitle() const;
    void addCO(const CourseOutcome& co);
    QVector<CourseOutcome> getCOs() const;
    void addExam(const Exam& exam);
    QVector<Exam> getExams() const;

private:
    QString code;
    QString title;
    QVector<CourseOutcome> cos;
    QVector<Exam> exams;
};

#endif // COURSE_H
