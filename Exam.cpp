#include "Exam.h"

Exam::Exam(Type type) : m_type(type) {}

Exam::Type Exam::getType() const { return m_type; }
QString Exam::getTypeString() const { return m_type == ISA ? "ISA" : "SEA"; }
void Exam::setCOMapping(int coId, double weight) { m_coMappings[coId] = weight; }
double Exam::getCOMapping(int coId) const { return m_coMappings.value(coId, 0.0); }
