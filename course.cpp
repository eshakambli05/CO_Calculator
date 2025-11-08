#include "course.h"

Course::Course(const QString& code, const QString& title) : code(code), title(title) {}

QString Course::getCode() const { return code; }
QString Course::getTitle() const { return title; }

void Course::addCO(const CourseOutcome& co) { cos.append(co); }
QVector<CourseOutcome> Course::getCOs() const { return cos; }

void Course::addExam(const Exam& exam) { exams.append(exam); }
QVector<Exam> Course::getExams() const { return exams; }
