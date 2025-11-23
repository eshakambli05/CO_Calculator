#include "Course.h"

// Constructor
Course::Course(const QString& code, const QString& title)
    : m_code(code), m_title(title)
{
}

// --- Basic Course Info ---

QString Course::getCode() const { return m_code; }
QString Course::getTitle() const { return m_title; }

// --- Course Outcomes (COs) ---

void Course::addCourseOutcome(const CourseOutcome& co) { m_cos.append(co); }
QList<CourseOutcome> Course::getCourseOutcomes() const { return m_cos; }

// --- Max Marks Configuration ---

void Course::setMaxISAMarks(int coIndex, double marks) { m_maxIsaMarks[coIndex] = marks; }
void Course::setMaxSEAMarks(int coIndex, double marks) { m_maxSeaMarks[coIndex] = marks; }
double Course::getMaxISAMarks(int coIndex) const { return m_maxIsaMarks.value(coIndex, 0.0); }
double Course::getMaxSEAMarks(int coIndex) const { return m_maxSeaMarks.value(coIndex, 0.0); }

// --- PSOs ---

void Course::addPSO(const ProgramSpecificOutcome& pso) { m_psos.append(pso); }
QList<ProgramSpecificOutcome> Course::getPSOs() const { return m_psos; }

// --- Program Outcomes (POs) ---

QList<ProgramOutcome> Course::getProgramOutcomes() const {
    QList<ProgramOutcome> pos;

    // POs based on the provided PDF (Goa University)
    pos.append(ProgramOutcome("PO1", "Expertise in specific areas of knowledge"));
    pos.append(ProgramOutcome("PO2", "Problem analysis"));
    pos.append(ProgramOutcome("PO3", "Design/development of solutions"));
    pos.append(ProgramOutcome("PO4", "Conduct investigations of complex problems"));
    pos.append(ProgramOutcome("PO5", "Modern tool usage"));
    pos.append(ProgramOutcome("PO6", "The Engineer and Society"));
    pos.append(ProgramOutcome("PO7", "Environment and sustainability"));
    pos.append(ProgramOutcome("PO8", "Ethics"));
    pos.append(ProgramOutcome("PO9", "Individual and teamwork"));
    pos.append(ProgramOutcome("PO10", "Communication"));
    pos.append(ProgramOutcome("PO11", "Project management and finance"));
    pos.append(ProgramOutcome("PO12", "Life-long learning"));

    return pos;
}

// --- Student Management ---

void Course::clearStudents() { m_students.clear(); }
void Course::addStudent(const Student& student) { m_students.append(student); }
QList<Student> Course::getStudents() const { return m_students; }
