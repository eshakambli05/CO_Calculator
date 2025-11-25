#include "Student.h"

Student::Student(const QString& name, const QString& rollNo)
    : m_name(name), m_rollNo(rollNo)
{
}

void Student::setISAMark(int coIndex, double marks) {
    m_isaMarks[coIndex] = marks;
}

void Student::setSEAMark(int coIndex, double marks) {
    m_seaMarks[coIndex] = marks;
}

double Student::getISAMark(int coIndex) const {
    return m_isaMarks.value(coIndex, 0.0);
}

double Student::getSEAMark(int coIndex) const {
    return m_seaMarks.value(coIndex, 0.0);
}

QString Student::getName() const {
    return m_name;
}

QString Student::getRollNo() const {
    return m_rollNo;
}
