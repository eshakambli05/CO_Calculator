#include "Course.h"

Course::Course(const QString& code, const QString& title)
    : m_code(code), m_title(title)
{
}

QString Course::getCode() const { return m_code; }
QString Course::getTitle() const { return m_title; }

// --- COs ---
void Course::addCourseOutcome(const CourseOutcome& co) { m_cos.append(co); }
QList<CourseOutcome> Course::getCourseOutcomes() const { return m_cos; }

// --- Max Marks ---
void Course::setMaxISAMarks(int coIndex, double marks) { m_maxIsaMarks[coIndex] = marks; }
void Course::setMaxSEAMarks(int coIndex, double marks) { m_maxSeaMarks[coIndex] = marks; }
double Course::getMaxISAMarks(int coIndex) const { return m_maxIsaMarks.value(coIndex, 0.0); }
double Course::getMaxSEAMarks(int coIndex) const { return m_maxSeaMarks.value(coIndex, 0.0); }

// --- PSOs ---
void Course::clearPSOs() { m_psos.clear(); }
void Course::addPSO(const QString& code, const QString& description) {
    m_psos.append({code, description});
}
QList<PSO> Course::getPSOs() const { return m_psos; }

// --- Mapping ---
void Course::setCorrelation(const QString& coCode, const QString& targetCode, int level) {
    m_mappingMatrix[coCode][targetCode] = level;
}
int Course::getCorrelation(const QString& coCode, const QString& targetCode) const {
    if (m_mappingMatrix.contains(coCode) && m_mappingMatrix[coCode].contains(targetCode)) {
        return m_mappingMatrix[coCode][targetCode];
    }
    return 0; // Default no correlation
}

// --- POs ---
QList<ProgramOutcome> Course::getProgramOutcomes() const {
    QList<ProgramOutcome> pos;

    // POs based on the provided PDF (Goa University)
    pos.append(ProgramOutcome("PO1", "Expertise in specific areas of knowledge: Develop an ability to be a specialist in at least one area of knowledge and apply the same in day-to-day practices."));
    pos.append(ProgramOutcome("PO2", "Problem analysis: Identify, formulate, and analyze complex problems in the area of specialization to reach substantiated conclusions using fundamental principles."));
    pos.append(ProgramOutcome("PO3", "Design/development of solutions: Design solutions for complex problems that meet the specified needs with appropriate consideration for public health and safety and the cultural, societal, and environmental considerations"));
    pos.append(ProgramOutcome("PO4", "Conduct investigations of complex problems: Use interdisciplinary research and technology knowledge, research literature, and research methods, including design of experiments, analysis and interpretation of data, and synthesis of the information to provide valid conclusions."));
    pos.append(ProgramOutcome("PO5", "Modern tool usage: Create, select, and apply appropriate techniques, resources, and modern engineering and IT tools including prediction and modeling to complex engineering activities with an understanding of the limitations."));
    pos.append(ProgramOutcome("PO6", "The Engineer and Society: Apply reasoning informed by the contextual knowledge to assess societal, health, safety, legal and cultural issues and the consequent responsibilities relevant to the professional engineering practice."));
    pos.append(ProgramOutcome("PO7", "Environment and sustainability: Understand the impact of the professional engineering solutions in societal and environmental contexts, and demonstrate the knowledge of, and need for sustainable development."));
    pos.append(ProgramOutcome("PO8", "Ethics: Apply ethical principles and commit to professional ethics and responsibilities and norms of the engineering practice."));
    pos.append(ProgramOutcome("PO9", "Individual and teamwork: Function effectively as an individual, and as a member or leader in diverse teams, and in multidisciplinary settings."));
    pos.append(ProgramOutcome("PO10", "Communication: Communicate effectively on complex engineering activities with the engineering community and with society at large, such as, being able to comprehend and write effective reports and design documentation, make effective presentations, and give and receive clear instructions."));
    pos.append(ProgramOutcome("PO11", "Project management and finance: Demonstrate knowledge and understanding of the engineering and management principles and apply these to one’s own work, as a member and leader in a team, to manage projects and in multidisciplinary environments."));
    pos.append(ProgramOutcome("PO12", "Life-long learning: Recognize the need for, and have the preparation and ability to engage in independent and life-long learning in the broadest context of technological change."));

    return pos;
}

// --- Students ---
void Course::clearStudents() { m_students.clear(); }
void Course::addStudent(const Student& student) { m_students.append(student); }
QList<Student> Course::getStudents() const { return m_students; }
