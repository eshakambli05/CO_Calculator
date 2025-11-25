#ifndef EXAM_H
#define EXAM_H

#include <QString>
#include <QMap>

class Exam {
public:
    enum Type { ISA, SEA };
    Exam(Type type = ISA);
    Type getType() const;
    QString getTypeString() const;
    void setCOMapping(int coId, double weight);
    double getCOMapping(int coId) const;

private:
    Type m_type;
    QMap<int, double> m_coMappings;  // coId -> weight
};

#endif // EXAM_H
