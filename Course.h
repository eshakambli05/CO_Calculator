#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QList>
#include <QMap>
#include "CourseOutcome.h"
#include "ProgramOutcome.h"
#include "ProgramSpecificOutcome.h"
#include "Student.h"
// Forward declaration for Faculty if needed, or include it
#include "Faculty.h"

class Course {
public:
    // Constructor
    Course(const QString& code = "", const QString& title = "");

    // Basic Info
    QString getCode() const;
    QString getTitle() const;

    // Course Outcomes
    void addCourseOutcome(const CourseOutcome& co);
    QList<CourseOutcome> getCourseOutcomes() const;

    // Max Marks Configuration
    void setMaxISAMarks(int coIndex, double marks);
    void setMaxSEAMarks(int coIndex, double marks);
    double getMaxISAMarks(int coIndex) const;
    double getMaxSEAMarks(int coIndex) const;

    // PSOs
    void addPSO(const ProgramSpecificOutcome& pso);
    QList<ProgramSpecificOutcome> getPSOs() const;

    // Program Outcomes
    QList<ProgramOutcome> getProgramOutcomes() const;

    // Student Management
    void clearStudents();
    void addStudent(const Student& student);
    QList<Student> getStudents() const;

private:
    QString m_code;
    QString m_title;
    QList<CourseOutcome> m_cos;
    QList<ProgramSpecificOutcome> m_psos;
    QList<Student> m_students;

    QMap<int, double> m_maxIsaMarks;
    QMap<int, double> m_maxSeaMarks;
};

#endif // COURSE_H
