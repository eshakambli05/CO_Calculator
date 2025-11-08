# CO_Calculator
GUI-based C++ system to help faculty record student marks, map Course Outcomes to Program Outcomes, and compute CO/PO/PSO attainment levels.

#  Course Outcome Attainment System (Qt / C++)

A Qt-based C++ GUI application for managing courses, mapping Course Outcomes (COs) to Program Outcomes (POs) and Program Specific Outcomes (PSOs), and automatically calculating attainment levels as per the Outcome-Based Education (OBE) framework.



##  Overview
The **Course Outcome Attainment System** helps faculty members efficiently calculate and track Course Outcome (CO) attainment for their courses.  
It allows faculty to:
- Define courses and outcomes (COs, POs, PSOs),
- Enter student marks for internal (ISA) and semester-end (SEA) exams,
- Automatically calculate attainment levels,
- And generate outcome-based reports aligned with the **Outcome-Based Education (OBE)** methodology.

This system simplifies manual calculations and report generation for academic departments and faculty coordinators.



## ✨ Features
-  **Faculty Management** – Add faculty details (name, email, department).  
-  **Course Management** – Create and manage multiple courses per faculty.  
-  **Outcome Management** – Add Course Outcomes (COs) and correlate them with predefined POs and user-defined PSOs.  
-  **CO–PO / CO–PSO Mapping** – Set correlation levels (Low = 1, Medium = 2, High = 3).  
-  **Exam Management** – Add Internal Assessments (ISA-1, ISA-2, etc.) and Semester-End Exams (SEA).  
-  **Marks Entry** – Enter student-wise CO marks for each exam.  
-  **Automatic Attainment Calculation** – Calculates:
  - CO attainment for each student and course
  - Attainment levels (Level 1–3)
  - Overall CO attainment (0.6 × ISA + 0.4 × SEA)  
-  **Reports Generation** – Displays CO Attainment Table, CO–PO and CO–PSO mapping, and student-wise performance.  
-  **Export Options** – (Optional) Export reports to CSV or PDF.

