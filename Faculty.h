#ifndef FACULTY_H
#define FACULTY_H

#include <QString>

class Faculty {
public:
    Faculty(const QString& name = "", const QString& email = "", const QString& department = "");
    QString getName() const;
    QString getEmail() const;
    QString getDepartment() const;
    void setName(const QString& name);
    void setEmail(const QString& email);
    void setDepartment(const QString& department);

private:
    QString m_name;
    QString m_email;
    QString m_department;
};

#endif // FACULTY_H
