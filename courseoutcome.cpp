#include "courseoutcome.h"

CourseOutcome::CourseOutcome(const QString& code, const QString& description)
    : code(code), description(description) {}

QString CourseOutcome::getCode() const { return code; }
QString CourseOutcome::getDescription() const { return description; }

void CourseOutcome::setPOMapping(const QString& po, int level) { poMapping[po] = level; }
QMap<QString, int> CourseOutcome::getPOMapping() const { return poMapping; }

void CourseOutcome::setPSOMapping(const QString& pso, int level) { psoMapping[pso] = level; }
QMap<QString, int> CourseOutcome::getPSOMapping() const { return psoMapping; }
