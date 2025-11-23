#include "Faculty.h"

Faculty::Faculty(const QString& name, const QString& email, const QString& department)
    : m_name(name), m_email(email), m_department(department) {}

QString Faculty::getName() const { return m_name; }
QString Faculty::getEmail() const { return m_email; }
QString Faculty::getDepartment() const { return m_department; }
void Faculty::setName(const QString& name) { m_name = name; }
void Faculty::setEmail(const QString& email) { m_email = email; }
void Faculty::setDepartment(const QString& department) { m_department = department; }
