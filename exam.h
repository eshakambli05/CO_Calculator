#ifndef EXAM_H
#define EXAM_H

#include <QString>
#include <QMap>

class Exam {
public:
    Exam(const QString& name);
    QString getName() const;
    void setCOMarks(const QString& co, int maxMarks);
    QMap<QString, int> getCOMarks() const;  // CO -> max marks

private:
    QString name;
    QMap<QString, int> coMarks;  // CO -> max marks
};

#endif // EXAM_H
