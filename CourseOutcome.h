#ifndef COURSEOUTCOME_H
#define COURSEOUTCOME_H

#include <QString>

class CourseOutcome {
public:
    CourseOutcome(const QString& code = "", const QString& description = "");
    QString getCode() const;
    QString getDescription() const;
    void setAttainmentLevel(int level);
    int getAttainmentLevel() const;

private:
    QString m_code;
    QString m_description;
    int m_attainmentLevel;  // 1, 2, or 3
};

#endif // COURSEOUTCOME_H
