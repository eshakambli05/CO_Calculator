#include "ReportGenerator.h"
#include "Course.h"
#include "Faculty.h"
#include "Student.h"
#include "CourseOutcome.h"
#include "COCalculator.h"

#include <QPrinter>
#include <QTextDocument>
#include <QDate>
#include <QDebug>
#include <utility>

ReportGenerator::ReportGenerator(QObject *parent) : QObject(parent)
{
}

bool ReportGenerator::generatePDF(const QString &filePath, const Course* course, const Faculty* faculty)
{
    if (!course || !faculty) return false;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize::A4);

    QTextDocument doc;
    doc.setHtml(createHtmlContent(course, faculty));
    doc.print(&printer);
    return true;
}

QString ReportGenerator::createHtmlContent(const Course* course, const Faculty* faculty)
{
    QString html = "<html><head><style>"
                   "body { font-family: Arial, sans-serif; font-size: 10pt; }"
                   "h1 { text-align: center; color: #2c3e50; }"
                   "p.meta { text-align: center; color: #555; font-size: 11pt; }"
                   "table { border-collapse: collapse; width: 100%; margin-top: 15px; }"
                   "th, td { border: 1px solid #444; padding: 6px; text-align: center; vertical-align: middle; }"
                   "th { background-color: #f2f2f2; font-weight: bold; }"
                   ".left { text-align: left; }"
                   // Color classes for levels
                   ".lvl3 { background-color: #90EE90; } " // Light Green
                   ".lvl2 { background-color: #FFFFE0; } " // Light Yellow
                   ".lvl1 { background-color: #FFD700; } " // Gold/Orange
                   ".lvl0 { background-color: #FFB6C1; } " // Light Red
                   "</style></head><body>";

    // --- Header ---
    html += "<h1>Course Attainment Report</h1>";
    html += QString("<p class='meta'><b>Course:</b> %1 (%2) <br> <b>Faculty:</b> %3 <br> <b>Date:</b> %4</p><hr>")
                .arg(course->getTitle())
                .arg(course->getCode())
                .arg(faculty->getName())
                .arg(QDate::currentDate().toString("dd MMM yyyy"));

    // --- Table: Student Attainment ---
    html += "<h3>Student Attainment Levels (Level & Percentage)</h3>";
    html += "<table><thead>";

    // Header Row 1: Student Info + CO Columns
    html += "<tr><th width='20%' class='left'>Student Name</th><th width='10%'>Roll No</th>";
    QList<CourseOutcome> cos = course->getCourseOutcomes();
    for(const auto& co : cos) {
        html += QString("<th colspan='2'>%1</th>").arg(co.getCode());
    }
    html += "</tr>";

    // Header Row 2: ISA / SEA Sub-columns
    html += "<tr><th></th><th></th>"; // Empty for Name/Roll
    for(int i=0; i<cos.size(); ++i) {
        html += "<th>ISA</th><th>SEA</th>";
    }
    html += "</tr></thead><tbody>";

    // --- Data Rows ---
    QList<Student> students = course->getStudents();

    // Safety limit for PDF generation
    int limit = qMin(static_cast<int>(students.size()), 200);

    for(int i=0; i<limit; ++i) {
        const Student& s = students[i];
        html += "<tr>";
        html += QString("<td class='left'>%1</td><td>%2</td>").arg(s.getName(), s.getRollNo());

        // For each CO, calculate ISA and SEA metrics
        for(int c=0; c<cos.size(); ++c) {
            // --- ISA ---
            double isaMax = course->getMaxISAMarks(c);
            auto isaRes = COCalculator::calculateMetric(s.getISAMark(c), isaMax); // returns {pct, lvl}
            QString isaClass = QString("lvl%1").arg(isaRes.second);

            html += QString("<td class='%1'>L%2<br><span style='font-size:8pt'>(%3%)</span></td>")
                        .arg(isaClass)
                        .arg(isaRes.second)
                        .arg(isaRes.first, 0, 'f', 0); // 0 decimal places

            // --- SEA ---
            double seaMax = course->getMaxSEAMarks(c);
            auto seaRes = COCalculator::calculateMetric(s.getSEAMark(c), seaMax);
            QString seaClass = QString("lvl%1").arg(seaRes.second);

            html += QString("<td class='%1'>L%2<br><span style='font-size:8pt'>(%3%)</span></td>")
                        .arg(seaClass)
                        .arg(seaRes.second)
                        .arg(seaRes.first, 0, 'f', 0);
        }
        html += "</tr>";
    }
    html += "</tbody></table>";

    html += "</body></html>";
    return html;
}
