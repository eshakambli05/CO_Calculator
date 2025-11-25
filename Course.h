#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QList>
#include <QMap>
#include "CourseOutcome.h"
#include "ProgramOutcome.h"
#include "Student.h"
#include "Faculty.h"

// Simple struct for PSO
struct PSO {
    QString code;
    QString description;
};

class Course {
public:
    Course(const QString& code = "", const QString& title = "");

    QString getCode() const;
    QString getTitle() const;

    // --- COs ---
    void addCourseOutcome(const CourseOutcome& co);
    QList<CourseOutcome> getCourseOutcomes() const;

    // --- Max Marks ---
    void setMaxISAMarks(int coIndex, double marks);
    void setMaxSEAMarks(int coIndex, double marks);
    double getMaxISAMarks(int coIndex) const;
    double getMaxSEAMarks(int coIndex) const;

    // --- PSOs (New) ---
    void clearPSOs();
    void addPSO(const QString& code, const QString& description);
    QList<PSO> getPSOs() const;

    // --- POs ---
    QList<ProgramOutcome> getProgramOutcomes() const;

    // --- Mapping (New) ---
    // Stores correlation: Key=CO_Code, Value=Map(Target_Code -> Level)
    void setCorrelation(const QString& coCode, const QString& targetCode, int level);
    int getCorrelation(const QString& coCode, const QString& targetCode) const;

    // --- Students ---
    void clearStudents();
    void addStudent(const Student& student);
    QList<Student> getStudents() const;

private:
    QString m_code;
    QString m_title;
    QList<CourseOutcome> m_cos;
    QList<PSO> m_psos;
    QList<Student> m_students;

    QMap<int, double> m_maxIsaMarks;
    QMap<int, double> m_maxSeaMarks;

    // Mapping Data: CO Code -> (PO/PSO Code -> Level)
    QMap<QString, QMap<QString, int>> m_mappingMatrix;
};

#endif // COURSE_H
