#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QObject>
#include <QString>

// Forward declarations to avoid circular dependencies
class Course;
class Faculty;

class ReportGenerator : public QObject
{
    Q_OBJECT
public:
    explicit ReportGenerator(QObject *parent = nullptr);

    /**
     * @brief Generates a PDF report for the given course and faculty.
     * @param filePath The full path where the PDF will be saved.
     * @param course Pointer to the Course object containing data.
     * @param faculty Pointer to the Faculty object containing details.
     * @return true if successful, false otherwise.
     */
    bool generatePDF(const QString &filePath, const Course* course, const Faculty* faculty);

private:
    // Helper to build the HTML string
    QString createHtmlContent(const Course* course, const Faculty* faculty);
};

#endif // REPORTGENERATOR_H
