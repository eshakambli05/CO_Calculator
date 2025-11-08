#ifndef PROGRAMSPECIFICOUTCOME_H
#define PROGRAMSPECIFICOUTCOME_H

#include <QString>

class ProgramSpecificOutcome {
public:
    ProgramSpecificOutcome(const QString& code, const QString& description);
    QString getCode() const;
    QString getDescription() const;

private:
    QString code;
    QString description;
};

#endif // PROGRAMSPECIFICOUTCOME_H
