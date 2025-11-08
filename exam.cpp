#include "exam.h"

Exam::Exam(const QString& name) : name(name) {}

QString Exam::getName() const { return name; }

void Exam::setCOMarks(const QString& co, int maxMarks) { coMarks[co] = maxMarks; }
QMap<QString, int> Exam::getCOMarks() const { return coMarks; }
