#include "Student.h"

// Constructor
Student::Student(const QString& name, const QString& rollNo)
    : m_name(name), m_rollNo(rollNo)
{
}

// --- Setters ---

void Student::setISAMark(int coIndex, double marks) {
    m_isaMarks[coIndex] = marks;
}

void Student::setSEAMark(int coIndex, double marks) {
    m_seaMarks[coIndex] = marks;
}

// --- Getters ---

double Student::getISAMark(int coIndex) const {
    // Return 0.0 if marks haven't been entered for this CO yet
    return m_isaMarks.value(coIndex, 0.0);
}

double Student::getSEAMark(int coIndex) const {
    // Return 0.0 if marks haven't been entered for this CO yet
    return m_seaMarks.value(coIndex, 0.0);
}

QString Student::getName() const {
    return m_name;
}

QString Student::getRollNo() const {
    return m_rollNo;
}
