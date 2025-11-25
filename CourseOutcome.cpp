#include "CourseOutcome.h"

CourseOutcome::CourseOutcome(const QString& code, const QString& description)
    : m_code(code), m_description(description), m_attainmentLevel(0) {}

QString CourseOutcome::getCode() const { return m_code; }
QString CourseOutcome::getDescription() const { return m_description; }
void CourseOutcome::setAttainmentLevel(int level) { m_attainmentLevel = level; }
int CourseOutcome::getAttainmentLevel() const { return m_attainmentLevel; }
