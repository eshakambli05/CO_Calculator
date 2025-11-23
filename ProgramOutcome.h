#ifndef PROGRAMOUTCOME_H
#define PROGRAMOUTCOME_H

#include <QString>

class ProgramOutcome {
public:
    ProgramOutcome(const QString& code = "", const QString& description = "");
    QString getCode() const;
    QString getDescription() const;

private:
    QString m_code;
    QString m_description;
};

#endif // PROGRAMOUTCOME_H
