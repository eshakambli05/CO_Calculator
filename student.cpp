#include "student.h"

Student::Student(const QString& name, const QString& rollNo) : name(name), rollNo(rollNo) {}

QString Student::getName() const { return name; }
QString Student::getRollNo() const { return rollNo; }

void Student::setMarks(const QString& exam, const QString& co, int marks) {
    marks[exam][co] = marks;
}

int Student::getMarks(const QString& exam, const QString& co) const {
    return marks.value(exam).value(co, 0);
}

QMap<QString, QMap<QString, int>> Student::getAllMarks() const { return marks; }
