# AI-Assisted Student Record and Result Management System

[![Language: C](https://img.shields.io/badge/Language-C99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![Compiler: GCC](https://img.shields.io/badge/Compiler-MinGW%20%2F%20GCC-green.svg)](https://gcc.gnu.org/)
[![Course: PRC1001](https://img.shields.io/badge/Course-PRC1001%20Programming%20in%20C-orange.svg)](https://www.upes.ac.in)
[![SAP ID: 590034676](https://img.shields.io/badge/SAP%20ID-590034676-purple.svg)](https://github.com/ridhimajalwi1907/student-record-ai-c-)

**Institution:** University of Petroleum and Energy Studies (UPES)  
**School:** School of Computer Science  
**Program:** B. Tech Computer Science & Engineering (Semester I)  
**Course Name:** Programming in C  
**Course Code:** PRC1001  
**Student Name:** Ridhima Jalwi  
**SAP ID:** 590034676  
**GitHub Repository:** [https://github.com/ridhimajalwi1907/student-record-ai-c-](https://github.com/ridhimajalwi1907/student-record-ai-c-)  

---

## 📌 Project Overview

The **AI-Assisted Student Record and Result Management System** is a robust, menu-driven console application engineered in standard C. It provides complete academic record maintenance, multi-semester SGPA/CGPA evaluation, year-wise analytics, and an integrated **AI-Assisted Academic Advisor** rule-based expert subsystem designed using AI prompt engineering.

The application allows academic administrators to add, view, search, delete, and sort student records, while providing students with actionable, tier-based academic recommendations derived deterministically from their cumulative performance.

---

## 🗂️ Repository Structure

In strict adherence to the project assignment guidelines:

```text
student-record-ai-c/
├── 590034676.c            # Complete C source file named with author SAP ID
├── README.md              # Project documentation, architecture & usage instructions
├── AI_USAGE_LOG.md        # Comprehensive log of AI interactions, prompts, & verifications
└── tests/
    ├── sample_input.txt   # Structured test inputs exercising all menu options
    └── sample_output.txt  # Complete console output generated during execution
```

---

## 🚀 Key Features

### Part A – Core C Programming Features
1. **Interactive Menu-Driven Architecture:** User-friendly console interface with validation on all inputs.
2. **Preloaded Records (At least 5 Students):** Pre-initialized with 5 comprehensive student records spanning 1st, 2nd, 3rd, and 4th academic years.
3. **Comprehensive Data Schema:** Stores SAP ID, Roll Number, Full Name, Contact Phone, Email Address, Academic Year (1st–4th), Current Semester (1–8), and SGPAs for all 8 semesters.
4. **Dynamic CGPA Calculation:** Averages only completed/available semester SGPAs (`sgpa >= 0.0`), gracefully handling uncompleted semesters (`-1.0f`).
5. **Year-Wise Performance Analytics:** Calculates and displays the average CGPA across all students in each individual academic year.
6. **Record Search Engine:** Rapid record retrieval by SAP ID displaying full profile, semester breakdown, and advisory diagnosis.
7. **Record Deletion with Confirmation:** Safely removes records by SAP ID with user confirmation (`y/n`) and shifts internal array entries.
8. **Dual Sorting Algorithms:**
   - **Numerical Sort by SAP ID:** Ascending sort using numerical comparison.
   - **Alphabetical Sort by Name:** Ascending sort using case-insensitive alphabetical comparison.
   - *Note:* Both sorting functions preserve the original database order using temporary array buffers.

### Part B – AI-Assisted Academic Advisor (Mini Project)
A rule-based expert decision system designed with AI prompt assistance that categorizes student academic standing into 4 distinct tiers and outputs personalized recommendations:

| CGPA Range | Performance Category | AI Recommendation |
| :--- | :--- | :--- |
| **$\ge 9.00$** | **Excellent Performance** | Outstanding academic record! Maintain current study rhythm. Recommended to engage in research publications, competitive programming, and target premier internships. |
| **$7.50 \le \text{CGPA} < 9.00$** | **Good Performance** | Consistent and solid performance. Maintain regular study schedule, focus on subjects where SGPA dropped below 8.0, and undertake domain-specific projects. |
| **$6.00 \le \text{CGPA} < 7.50$** | **Needs Improvement** | Moderate performance. Focus more on core subjects with lower SGPA, seek regular faculty mentoring, and dedicate 2 hours daily for concept reinforcement. |
| **$< 6.00$** | **Requires Immediate Attention** | Academic warning zone. Immediate intervention needed: attend remedial classes, consult academic counselor, solve previous years' papers, and rebuild foundational concepts. |

---

## 🛠️ Compilation and Execution Instructions

### Prerequisites
- Any standard C compiler supporting C99 or later (GCC, Clang, or MSVC).
- MinGW / GCC is recommended.

### Step-by-Step Build Commands

1. **Compile with GCC:**
   ```bash
   gcc -Wall -Wextra -std=c99 590034676.c -o student_system.exe
   ```

2. **Run Interactively:**
   ```bash
   ./student_system.exe
   ```

3. **Run with Automated Test Input:**
   ```bash
   ./student_system.exe < tests/sample_input.txt > tests/sample_output.txt
   ```

---

## 📋 Menu Navigation Guide

```text
------------- MAIN MENU -------------
 1. Add Student Details
 2. Search and Display Student Record (by SAP ID)
 3. Calculate CGPA of All Students
 4. Calculate Average CGPA for Each Academic Year
 5. Display Records of All Students
 6. Delete an Individual Student Record
 7. Display All Records in Increasing Order of SAP ID
 8. Display All Records in Increasing Order of Name
 9. AI-Assisted Academic Advisor (CGPA-Based Recommendations)
 10. AI Advisor Demonstration (3 Distinct CGPA Cases)
 11. Exit
-------------------------------------
```

---

## 🧪 Demonstration of Distinct CGPA Cases

The program includes an automated multi-case demonstration function (Option 10) verifying all 4 performance tiers:
- **Case 1 (CGPA: 9.40):** *Excellent Performance*
- **Case 2 (CGPA: 8.30):** *Good Performance*
- **Case 3 (CGPA: 7.02):** *Needs Improvement*
- **Case 4 (CGPA: 5.40):** *Requires Immediate Attention*

---

## 🔄 GitHub Development Workflow & Commit History

As required by the assignment guidelines (minimum 4 meaningful commits):

1. **Commit 1 (`feat: initial c program skeleton and data structures`):**  
   Defined `Student` structure, menu-driven loop, safe input utility functions (`readLine`, `readInt`, `readLongLong`), and default data initialization.
2. **Commit 2 (`feat: implement core student record management functions`):**  
   Added `addStudent()`, `searchStudent()`, `deleteStudent()`, and tabular `displayAllStudents()`.
3. **Commit 3 (`feat: implement cgpa calculation and sorting functions`):**  
   Implemented dynamic available SGPA averaging (`calculateCGPA`), year-wise average analytics (`calculateYearlyAverageCGPA`), and dual sorting algorithms (by SAP ID and Name).
4. **Commit 4 (`feat: integrate ai academic advisor, test suite, and documentation`):**  
   Integrated AI-guided decision-making logic (`getAIAdvice()`), automated multi-tier demonstration, test inputs/outputs (`tests/sample_input.txt`, `tests/sample_output.txt`), `AI_USAGE_LOG.md`, and comprehensive `README.md`.

### GitHub Issue Tracking
- **Issue #1:** [Implement dynamic CGPA calculation and test search function](https://github.com/ridhimajalwi1907/student-record-ai-c-/issues/1) — *Resolved and Closed as Completed*.

---

## 🎓 Viva Preparation Notes

- **How CGPA is calculated:** CGPA is computed by summing all valid SGPA values (`sgpa[i] >= 0.0`) and dividing by the count of completed semesters. Semesters not yet completed remain initialized to `-1.0f` and do not skew the average.
- **Buffer Safety in C:** The program replaces error-prone `scanf("%s")` with `fgets`-based `readLine()` and numerical validation parsers (`readInt`, `readLongLong`, `readFloat`), preventing buffer overflow, trailing newline corruption, and infinite input loops.
- **Sorting Mechanism:** Uses Bubble Sort on an isolated clone of the student database array, ensuring alphabetical (`tolower` character-by-character comparison) and numerical order without modifying user insertion order.
- **AI Integration:** AI was utilized to conceptualize actionable academic advising feedback categories and generate boundary test cases. The resulting logic was verified and implemented natively in C using deterministic `if-else` branching without external runtime dependencies.
