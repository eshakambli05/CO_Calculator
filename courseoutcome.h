#ifndef COURSEOUTCOME_H
#define COURSEOUTCOME_H

#include <QString>
#include <QMap>

class CourseOutcome {
public:
    CourseOutcome(const QString& code, const QString& description);
    QString getCode() const;
    QString getDescription() const;
    void setPOMapping(const QString& po, int level);
    QMap<QString, int> getPOMapping() const;
    void setPSOMapping(const QString& pso, int level);
    QMap<QString, int> getPSOMapping() const;

private:
    QString code;
    QString description;
    QMap<QString, int> poMapping;  // PO code -> level (1-3)
    QMap<QString, int> psoMapping; // PSO code -> level (1-3)
};

#endif // COURSEOUTCOME_H
