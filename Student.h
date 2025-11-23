#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QMap>

class Student {
public:
    // Constructor
    Student(const QString& name = "", const QString& rollNo = "");

    // Getters
    QString getName() const;
    QString getRollNo() const;

    // Setters
    void setISAMark(int coIndex, double marks);
    void setSEAMark(int coIndex, double marks);

    // Getters for Marks
    double getISAMark(int coIndex) const;
    double getSEAMark(int coIndex) const;

private:
    QString m_name;
    QString m_rollNo;
    QMap<int, double> m_isaMarks; // CO Index -> Marks
    QMap<int, double> m_seaMarks; // CO Index -> Marks
};

#endif // STUDENT_H
