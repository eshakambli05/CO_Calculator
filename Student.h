#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QMap>

class Student
{
public:
    Student(const QString& name, const QString& rollNo);

    void setISAMark(int coIndex, double marks);
    void setSEAMark(int coIndex, double marks);

    double getISAMark(int coIndex) const;
    double getSEAMark(int coIndex) const;

    QString getName() const;
    QString getRollNo() const;

private:
    QString m_name;
    QString m_rollNo;

    QMap<int,double> m_isaMarks;
    QMap<int,double> m_seaMarks;
};

#endif // STUDENT_H
