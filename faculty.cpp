#include "faculty.h"

Faculty::Faculty(const QString& name, const QString& email, const QString& department)
    : name(name), email(email), department(department) {}

QString Faculty::getName() const { return name; }
QString Faculty::getEmail() const { return email; }
QString Faculty::getDepartment() const { return department; }
