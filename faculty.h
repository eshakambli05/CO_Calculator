#ifndef FACULTY_H
#define FACULTY_H

#include <QString>

class Faculty {
public:
    Faculty(const QString& name, const QString& email, const QString& department);
    QString getName() const;
    QString getEmail() const;
    QString getDepartment() const;

private:
    QString name;
    QString email;
    QString department;
};

#endif // FACULTY_H
