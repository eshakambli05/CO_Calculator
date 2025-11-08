#include "programspecificoutcome.h"

ProgramSpecificOutcome::ProgramSpecificOutcome(const QString& code, const QString& description)
    : code(code), description(description) {}

QString ProgramSpecificOutcome::getCode() const { return code; }
QString ProgramSpecificOutcome::getDescription() const { return description; }
