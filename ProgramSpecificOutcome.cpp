#include "ProgramSpecificOutcome.h"

ProgramSpecificOutcome::ProgramSpecificOutcome(const QString& code, const QString& description)
    : m_code(code), m_description(description) {}

QString ProgramSpecificOutcome::getCode() const { return m_code; }
QString ProgramSpecificOutcome::getDescription() const { return m_description; }
