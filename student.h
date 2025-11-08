#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QMap>

class Student {
public:
    Student(const QString& name, const QString& rollNo);
    QString getName() const;
    QString getRollNo() const;
    void setMarks(const QString& exam, const QString& co, int marks);
    int getMarks(const QString& exam, const QString& co) const;
    QMap<QString, QMap<QString, int>> getAllMarks() const;  // exam -> co -> marks

private:
    QString name;
    QString rollNo;
    QMap<QString, QMap<QString, int>> marks;  // exam -> co -> marks
};

#endif // STUDENT_H
