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
#include <vector>
#include <numeric>

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
    // Standard A4 margins
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument doc;
    doc.setHtml(createHtmlContent(course, faculty));
    doc.print(&printer);
    return true;
}

QString ReportGenerator::createHtmlContent(const Course* course, const Faculty* faculty)
{
    // CSS Styling matching your sample images
    QString html = "<html><head><style>"
                   "body { font-family: 'Segoe UI', Arial, sans-serif; font-size: 10pt; color: #333; }"
                   "h1 { text-align: center; color: #2c3e50; font-size: 16pt; margin-bottom: 5px; text-transform: uppercase; border-bottom: 2px solid #2c3e50; padding-bottom: 10px; }"
                   "h3 { color: #0056b3; margin-top: 20px; margin-bottom: 10px; border-left: 5px solid #0056b3; padding-left: 10px; font-size: 12pt; background-color: #f0f8ff; }"

                   // Metadata Box Style
                   ".meta-box { border: 1px solid #ccc; padding: 10px; background-color: #f9f9f9; margin-bottom: 20px; font-size: 10pt; }"
                   ".meta-row { margin-bottom: 4px; }"
                   ".meta-label { font-weight: bold; width: 140px; display: inline-block; color: #555; }"

                   // Table Style
                   "table { border-collapse: collapse; width: 100%; margin-top: 5px; font-size: 9pt; }"
                   "th, td { border: 1px solid #444; padding: 6px; text-align: center; vertical-align: middle; }"
                   "th { background-color: #e6e6e6; font-weight: bold; color: #000; }"

                   // Specific column alignments
                   ".left { text-align: left; padding-left: 8px; }"
                   ".right { text-align: right; padding-right: 8px; }"

                   // Color Coding Classes
                   ".lvl3 { background-color: #c8e6c9; color: #256029; font-weight: bold; } " // Light Green
                   ".lvl2 { background-color: #fff9c4; color: #fbc02d; } " // Light Yellow
                   ".lvl1 { background-color: #ffccbc; color: #bf360c; } " // Light Orange
                   ".lvl0 { background-color: #ffcdd2; color: #c62828; } " // Light Red

                   // Final Calculation Row Highlighting
                   ".final-row { background-color: #e1f5fe; font-weight: bold; }"
                   ".final-val { color: #01579b; font-weight: bold; font-size: 10pt; }"

                   // Footer
                   ".footer { margin-top: 40px; font-size: 8pt; text-align: center; color: #888; border-top: 1px solid #eee; padding-top: 10px; }"
                   "</style></head><body>";

    // --- Header & Metadata ---
    html += "<h1>Course Outcome Attainment Report</h1>";

    html += "<div class='meta-box'>";
    html += QString("<div class='meta-row'><span class='meta-label'>Course:</span> %1 (%2)</div>").arg(course->getTitle(), course->getCode());
    html += QString("<div class='meta-row'><span class='meta-label'>Faculty:</span> %1</div>").arg(faculty->getName());
    html += QString("<div class='meta-row'><span class='meta-label'>Department:</span> %1</div>").arg(faculty->getDepartment());
    html += QString("<div class='meta-row'><span class='meta-label'>Generated On:</span> %1</div>").arg(QDate::currentDate().toString("dd MMMM yyyy"));
    html += "</div>";

    // ---------------------------------------------------------
    // SECTION 1: CO-PO-PSO Mapping Matrix
    // ---------------------------------------------------------
    html += "<h3>1. CO-PO-PSO Mapping Matrix</h3>";
    html += "<table><thead><tr><th width='10%'>CO</th>";

    // PO Headers
    for(int i=1; i<=12; ++i) html += QString("<th>PO%1</th>").arg(i);
    // PSO Headers
    QList<PSO> psos = course->getPSOs();
    for(const auto& pso : psos) html += QString("<th>%1</th>").arg(pso.code);
    html += "</tr></thead><tbody>";

    QList<CourseOutcome> cos = course->getCourseOutcomes();
    for(const auto& co : cos) {
        html += QString("<tr><td><b>%1</b></td>").arg(co.getCode());

        // PO Values
        for(int i=1; i<=12; ++i) {
            int val = course->getCorrelation(co.getCode(), QString("PO%1").arg(i));
            html += QString("<td>%1</td>").arg(val > 0 ? QString::number(val) : "-");
        }

        // PSO Values
        for(const auto& pso : psos) {
            int val = course->getCorrelation(co.getCode(), pso.code);
            html += QString("<td>%1</td>").arg(val > 0 ? QString::number(val) : "-");
        }
        html += "</tr>";
    }
    html += "</tbody></table>";

    // ---------------------------------------------------------
    // PRE-CALCULATION: Average CO Attainment
    // ---------------------------------------------------------
    std::vector<double> finalCOAttainments(cos.size(), 0.0);
    QList<Student> students = course->getStudents();

    // Calculate average attainment level for each CO across all students
    for(int c=0; c<cos.size(); ++c) {
        double sumLevels = 0;
        int count = 0;
        for(const auto& s : students) {
            // Get ISA Level
            double isaMax = course->getMaxISAMarks(c);
            auto rI = COCalculator::calculateMetric(s.getISAMark(c), isaMax);

            // Get SEA Level
            double seaMax = course->getMaxSEAMarks(c);
            auto rS = COCalculator::calculateMetric(s.getSEAMark(c), seaMax);

            // Average of ISA & SEA levels for this student
            double avgLevel = (double)(rI.second + rS.second) / 2.0;
            sumLevels += avgLevel;
            count++;
        }
        if(count > 0) finalCOAttainments[c] = sumLevels / count;
    }

    // ---------------------------------------------------------
    // SECTION 2: Final PO & PSO Attainment Calculation
    // ---------------------------------------------------------
    html += "<h3>2. Final Attainment Calculation</h3>";

    // Display Formula for clarity
    html += "<p style='font-size:9pt; color:#666;'><i>Formula: &Sigma; (CO Attainment Level × Mapping Level) / &Sigma; Mapping Levels</i></p>";

    html += "<table style='width:70%; margin:auto;'>";
    html += "<thead><tr><th class='left'>Outcome Code</th><th class='left'>Description</th><th>Calculated Attainment</th></tr></thead><tbody>";

    // PO Attainment Rows
    QList<ProgramOutcome> pos = course->getProgramOutcomes(); // Ensure your Course class has this getter working correctly or use hardcoded PO1-12 loop
    for(int i=1; i<=12; ++i) {
        QString poCode = QString("PO%1").arg(i);
        // Find description if available, else use generic
        QString desc = (i <= pos.size()) ? pos[i-1].getDescription() : "Program Outcome " + QString::number(i);

        std::vector<int> mappings;
        for(const auto& co : cos) mappings.push_back(course->getCorrelation(co.getCode(), poCode));

        double attain = COCalculator::calculatePOAttainment(finalCOAttainments, mappings);

        // Only show rows with attainment > 0 to keep report clean
        if(attain > 0.01) {
            html += QString("<tr class='final-row'><td class='left'><b>%1</b></td><td class='left' style='font-size:8pt;'>%2</td><td class='final-val'>%3</td></tr>")
            .arg(poCode)
                .arg(desc)
                .arg(attain, 0, 'f', 2);
        }
    }

    // PSO Attainment Rows
    for(const auto& pso : psos) {
        std::vector<int> mappings;
        for(const auto& co : cos) mappings.push_back(course->getCorrelation(co.getCode(), pso.code));

        double attain = COCalculator::calculatePOAttainment(finalCOAttainments, mappings);

        if(attain > 0.01) {
            html += QString("<tr class='final-row'><td class='left'><b>%1</b></td><td class='left' style='font-size:8pt;'>%2</td><td class='final-val'>%3</td></tr>")
            .arg(pso.code)
                .arg(pso.description)
                .arg(attain, 0, 'f', 2);
        }
    }
    html += "</tbody></table>";

    // ---------------------------------------------------------
    // SECTION 3: Detailed Student Attainment
    // ---------------------------------------------------------
    html += "<br>"; // Spacer
    html += "<h3>3. Detailed Student Attainment Analysis</h3>";
    html += "<table><thead>";

    // Header Row 1
    html += "<tr><th rowspan='2' width='5%'>Roll No</th><th rowspan='2' width='20%' class='left'>Student Name</th>";
    for(const auto& co : cos) {
        html += QString("<th colspan='2'>%1</th>").arg(co.getCode());
    }
    html += "</tr>";

    // Header Row 2
    html += "<tr>";
    for(int i=0; i<cos.size(); ++i) {
        html += "<th style='font-size:8pt; background-color:#f0f0f0;'>ISA</th><th style='font-size:8pt; background-color:#f0f0f0;'>SEA</th>";
    }
    html += "</tr></thead><tbody>";

    // Student Data Rows
    int limit = qMin(static_cast<int>(students.size()), 300); // PDF Safety Limit
    for(int i=0; i<limit; ++i) {
        const Student& s = students[i];
        html += "<tr>";
        html += QString("<td>%1</td><td class='left'>%2</td>").arg(s.getRollNo(), s.getName());

        for(int c=0; c<cos.size(); ++c) {
            // ISA Cell
            double isaMax = course->getMaxISAMarks(c);
            auto isaRes = COCalculator::calculateMetric(s.getISAMark(c), isaMax);
            html += QString("<td class='lvl%1'>L%2<br><span style='font-size:7pt'>(%3%)</span></td>")
                        .arg(isaRes.second) // Class for color
                        .arg(isaRes.second) // Level
                        .arg(isaRes.first, 0, 'f', 0); // Percentage

            // SEA Cell
            double seaMax = course->getMaxSEAMarks(c);
            auto seaRes = COCalculator::calculateMetric(s.getSEAMark(c), seaMax);
            html += QString("<td class='lvl%1'>L%2<br><span style='font-size:7pt'>(%3%)</span></td>")
                        .arg(seaRes.second)
                        .arg(seaRes.second)
                        .arg(seaRes.first, 0, 'f', 0);
        }
        html += "</tr>";
    }
    html += "</tbody></table>";

    // --- Footer ---
    html += "<div class='footer'>";
    html += "Generated automatically by the Outcome Attainment System software.<br>";
    html += "</div>";

    html += "</body></html>";

    return html;
}
