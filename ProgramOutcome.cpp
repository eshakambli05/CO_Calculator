#include "ProgramOutcome.h"

ProgramOutcome::ProgramOutcome(const QString& code, const QString& description)
    : m_code(code), m_description(description) {}

QString ProgramOutcome::getCode() const { return m_code; }
QString ProgramOutcome::getDescription() const { return m_description; }
