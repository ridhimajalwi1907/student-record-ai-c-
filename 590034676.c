/*
 * =====================================================================================
 * Project Title : AI-Assisted Student Record and Result Management System
 * Course Code   : PRC1001 (Programming in C)
 * Program       : B. Tech CSE - Semester I
 * Institution   : University of Petroleum and Energy Studies (UPES)
 * Student Name  : Ridhima Jalwi
 * SAP ID        : 590034676
 * =====================================================================================
 */

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define NUM_SEMESTERS 8
#define INITIAL_STUDENT_COUNT 5

/* =====================================================================================
 * Student Structure Definition
 * =====================================================================================
 */
typedef struct {
    long long sap_id;           /* UPES SAP ID (e.g., 590034676) */
    char roll_no[30];          /* University Roll Number (e.g., R214223001) */
    char name[60];             /* Student Full Name */
    char phone_no[20];         /* Contact Phone Number */
    char email_id[60];         /* University / Personal Email ID */
    int year;                  /* Academic Year: 1, 2, 3, or 4 */
    int semester;              /* Current Semester: 1 through 8 */
    float sgpa[NUM_SEMESTERS]; /* SGPA for all 8 semesters (-1.0 if not yet completed) */
} Student;

/* Global student database */
Student students[MAX_STUDENTS];
int student_count = 0;

/* =====================================================================================
 * Function Prototypes
 * =====================================================================================
 */
void readLine(char *buffer, int size);
int readInt(int *out);
float readFloat(float *out);
long long readLongLong(long long *out);
float calculateCGPA(const Student *s);
int getAvailableSGPACount(const Student *s);
void initializeDefaultRecords(void);
int findStudentIndexBySAP(long long sap_id);

/* Core C Assignment Functions */
void addStudent(void);
void searchStudent(void);
void calculateAndDisplayAllCGPA(void);
void calculateYearlyAverageCGPA(void);
void displayAllStudents(void);
void deleteStudent(void);
void displaySortedBySAP(void);
void displaySortedByName(void);

/* Part B: AI-Assisted Academic Advisor Functions */
void getAIAdvice(float cgpa, char *category_out, char *advice_out);
void runAcademicAdvisor(void);
void printAdvisorDemoCases(void);

/* Display Utilities */
void printStudentDetailed(const Student *s);
void printTableHeader(void);
void printStudentTableRow(const Student *s);

/* =====================================================================================
 * Main Function - Menu-Driven Architecture
 * =====================================================================================
 */
int main(void) {
    int choice = 0;

    /* Initialize system with 5 realistic student records as per assignment requirements */
    initializeDefaultRecords();

    printf("\n======================================================================\n");
    printf("   UNIVERSITY OF PETROLEUM AND ENERGY STUDIES (UPES)\n");
    printf("   Department of Computer Science & Engineering\n");
    printf("   PRC1001: Programming in C - Project-Based Assignment\n");
    printf("   Project: AI-Assisted Student Record & Result Management System\n");
    printf("   Author SAP ID: 590034676\n");
    printf("======================================================================\n");

    while (1) {
        printf("\n------------- MAIN MENU -------------\n");
        printf(" 1. Add Student Details\n");
        printf(" 2. Search and Display Student Record (by SAP ID)\n");
        printf(" 3. Calculate CGPA of All Students\n");
        printf(" 4. Calculate Average CGPA for Each Academic Year\n");
        printf(" 5. Display Records of All Students\n");
        printf(" 6. Delete an Individual Student Record\n");
        printf(" 7. Display All Records in Increasing Order of SAP ID\n");
        printf(" 8. Display All Records in Increasing Order of Name\n");
        printf(" 9. AI-Assisted Academic Advisor (CGPA-Based Recommendations)\n");
        printf(" 10. AI Advisor Demonstration (3 Distinct CGPA Cases)\n");
        printf(" 11. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice (1-11): ");

        if (!readInt(&choice)) {
            printf("\n[ERROR] Invalid input. Please enter a numerical menu option (1-11).\n");
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                calculateAndDisplayAllCGPA();
                break;
            case 4:
                calculateYearlyAverageCGPA();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                deleteStudent();
                break;
            case 7:
                displaySortedBySAP();
                break;
            case 8:
                displaySortedByName();
                break;
            case 9:
                runAcademicAdvisor();
                break;
            case 10:
                printAdvisorDemoCases();
                break;
            case 11:
                printf("\nExiting Student Record Management System. Thank you!\n");
                return 0;
            default:
                printf("\n[ERROR] Choice out of range. Please choose between 1 and 11.\n");
                break;
        }
    }

    return 0;
}

/* =====================================================================================
 * Helper Functions - Safe Robust Input Handling
 * =====================================================================================
 */

/* Reads a line of text safely, removing newline characters */
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\r') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

/* Reads an integer safely from user input */
int readInt(int *out) {
    char buf[128];
    char *endptr;
    readLine(buf, sizeof(buf));
    if (strlen(buf) == 0) return 0;
    *out = (int)strtol(buf, &endptr, 10);
    return (endptr != buf);
}

/* Reads a float safely from user input */
float readFloat(float *out) {
    char buf[128];
    char *endptr;
    readLine(buf, sizeof(buf));
    if (strlen(buf) == 0) return 0;
    *out = (float)strtod(buf, &endptr);
    return (endptr != buf);
}

/* Reads a 64-bit long long safely from user input */
long long readLongLong(long long *out) {
    char buf[128];
    char *endptr;
    readLine(buf, sizeof(buf));
    if (strlen(buf) == 0) return 0;
    *out = (long long)strtoll(buf, &endptr, 10);
    return (endptr != buf);
}

/* Calculates CGPA by taking the average of all available (completed) SGPA values */
float calculateCGPA(const Student *s) {
    float sum = 0.0f;
    int count = 0;
    int i;

    for (i = 0; i < NUM_SEMESTERS; i++) {
        if (s->sgpa[i] >= 0.0f) {
            sum += s->sgpa[i];
            count++;
        }
    }

    if (count == 0) {
        return 0.0f;
    }
    return sum / (float)count;
}

/* Returns the count of available SGPA entries */
int getAvailableSGPACount(const Student *s) {
    int count = 0;
    int i;
    for (i = 0; i < NUM_SEMESTERS; i++) {
        if (s->sgpa[i] >= 0.0f) {
            count++;
        }
    }
    return count;
}

/* Finds array index of a student by SAP ID, returns -1 if not found */
int findStudentIndexBySAP(long long sap_id) {
    int i;
    for (i = 0; i < student_count; i++) {
        if (students[i].sap_id == sap_id) {
            return i;
        }
    }
    return -1;
}

/* Initializes database with 5 complete, realistic student records across different years */
void initializeDefaultRecords(void) {
    int i, j;
    student_count = INITIAL_STUDENT_COUNT;

    /* Initialize all SGPAs to -1.0 (uncompleted) */
    for (i = 0; i < MAX_STUDENTS; i++) {
        for (j = 0; j < NUM_SEMESTERS; j++) {
            students[i].sgpa[j] = -1.0f;
        }
    }

    /* Record 1: 1st Year student (Author's SAP ID 590034676) */
    students[0].sap_id = 590034676LL;
    strcpy(students[0].roll_no, "R214223001");
    strcpy(students[0].name, "Ridhima Jalwi");
    strcpy(students[0].phone_no, "9876543210");
    strcpy(students[0].email_id, "ridhima.590034676@stu.upes.ac.in");
    students[0].year = 1;
    students[0].semester = 1;
    students[0].sgpa[0] = 9.40f; /* High CGPA -> Excellent Performance */

    /* Record 2: 2nd Year student */
    students[1].sap_id = 590034102LL;
    strcpy(students[1].roll_no, "R214223045");
    strcpy(students[1].name, "Aarav Sharma");
    strcpy(students[1].phone_no, "9811223344");
    strcpy(students[1].email_id, "aarav.sharma@stu.upes.ac.in");
    students[1].year = 2;
    students[1].semester = 3;
    students[1].sgpa[0] = 8.20f;
    students[1].sgpa[1] = 8.40f; /* CGPA = 8.30 -> Good Performance */

    /* Record 3: 3rd Year student */
    students[2].sap_id = 590034215LL;
    strcpy(students[2].roll_no, "R214223089");
    strcpy(students[2].name, "Ananya Verma");
    strcpy(students[2].phone_no, "9822334455");
    strcpy(students[2].email_id, "ananya.verma@stu.upes.ac.in");
    students[2].year = 3;
    students[2].semester = 5;
    students[2].sgpa[0] = 7.00f;
    students[2].sgpa[1] = 7.20f;
    students[2].sgpa[2] = 6.80f;
    students[2].sgpa[3] = 7.10f; /* CGPA = 7.025 -> Needs Improvement */

    /* Record 4: 1st Year student */
    students[3].sap_id = 590034330LL;
    strcpy(students[3].roll_no, "R214223120");
    strcpy(students[3].name, "Rohan Gupta");
    strcpy(students[3].phone_no, "9833445566");
    strcpy(students[3].email_id, "rohan.gupta@stu.upes.ac.in");
    students[3].year = 1;
    students[3].semester = 2;
    students[3].sgpa[0] = 5.40f; /* CGPA = 5.40 -> Requires Immediate Attention */

    /* Record 5: 4th Year student */
    students[4].sap_id = 590034450LL;
    strcpy(students[4].roll_no, "R214223155");
    strcpy(students[4].name, "Diya Patel");
    strcpy(students[4].phone_no, "9844556677");
    strcpy(students[4].email_id, "diya.patel@stu.upes.ac.in");
    students[4].year = 4;
    students[4].semester = 7;
    students[4].sgpa[0] = 8.80f;
    students[4].sgpa[1] = 9.10f;
    students[4].sgpa[2] = 8.90f;
    students[4].sgpa[3] = 9.30f;
    students[4].sgpa[4] = 9.00f;
    students[4].sgpa[5] = 9.20f; /* CGPA = 9.05 -> Excellent Performance */
}

/* =====================================================================================
 * Core C Programming Requirement Functions
 * =====================================================================================
 */

/* 13. Provide a function to add student details */
void addStudent(void) {
    Student s;
    int completed_sems = 0;
    int i;

    if (student_count >= MAX_STUDENTS) {
        printf("\n[ERROR] Student database is full (Maximum %d records).\n", MAX_STUDENTS);
        return;
    }

    printf("\n--- ADD NEW STUDENT RECORD ---\n");

    /* Prompt SAP ID */
    printf("Enter SAP ID (e.g. 590034676): ");
    if (!readLongLong(&s.sap_id) || s.sap_id <= 0) {
        printf("[ERROR] Invalid SAP ID. Operation aborted.\n");
        return;
    }

    /* Check uniqueness of SAP ID */
    if (findStudentIndexBySAP(s.sap_id) != -1) {
        printf("[ERROR] Student with SAP ID %lld already exists in the system!\n", s.sap_id);
        return;
    }

    /* Prompt Roll Number */
    printf("Enter Roll Number (e.g. R214223001): ");
    readLine(s.roll_no, sizeof(s.roll_no));
    if (strlen(s.roll_no) == 0) {
        printf("[ERROR] Roll number cannot be empty.\n");
        return;
    }

    /* Prompt Name */
    printf("Enter Full Name: ");
    readLine(s.name, sizeof(s.name));
    if (strlen(s.name) == 0) {
        printf("[ERROR] Name cannot be empty.\n");
        return;
    }

    /* Prompt Phone Number */
    printf("Enter Phone Number: ");
    readLine(s.phone_no, sizeof(s.phone_no));

    /* Prompt Email ID */
    printf("Enter Email ID: ");
    readLine(s.email_id, sizeof(s.email_id));

    /* Prompt Academic Year */
    printf("Enter Academic Year (1st=1, 2nd=2, 3rd=3, 4th=4): ");
    if (!readInt(&s.year) || s.year < 1 || s.year > 4) {
        printf("[ERROR] Academic Year must be between 1 and 4.\n");
        return;
    }

    /* Prompt Current Semester */
    printf("Enter Current Semester (1 to 8): ");
    if (!readInt(&s.semester) || s.semester < 1 || s.semester > 8) {
        printf("[ERROR] Semester must be between 1 and 8.\n");
        return;
    }

    /* Initialize all 8 semesters to -1.0 */
    for (i = 0; i < NUM_SEMESTERS; i++) {
        s.sgpa[i] = -1.0f;
    }

    /* Prompt for number of completed semesters with available SGPA */
    printf("Enter number of completed semesters with available SGPA (0 to %d): ", s.semester);
    if (!readInt(&completed_sems) || completed_sems < 0 || completed_sems > s.semester) {
        printf("[ERROR] Completed semesters must be between 0 and current semester (%d).\n", s.semester);
        return;
    }

    /* Prompt SGPA for each available semester */
    for (i = 0; i < completed_sems; i++) {
        float val;
        printf("  Enter SGPA for Semester %d (0.00 to 10.00): ", i + 1);
        if (!readFloat(&val) || val < 0.0f || val > 10.0f) {
            printf("[ERROR] Invalid SGPA value. Please enter a value between 0.00 and 10.00.\n");
            i--; /* Retry this semester */
            continue;
        }
        s.sgpa[i] = val;
    }

    students[student_count++] = s;
    printf("\n[SUCCESS] Student record for '%s' (SAP ID: %lld) added successfully!\n", s.name, s.sap_id);
    printf("Calculated CGPA: %.2f\n", calculateCGPA(&s));
}

/* 14. Provide a function to search and display a student record */
void searchStudent(void) {
    long long search_sap;
    int idx;

    if (student_count == 0) {
        printf("\n[INFO] No student records available to search.\n");
        return;
    }

    printf("\n--- SEARCH STUDENT RECORD ---\n");
    printf("Enter SAP ID to search: ");
    if (!readLongLong(&search_sap)) {
        printf("[ERROR] Invalid SAP ID format.\n");
        return;
    }

    idx = findStudentIndexBySAP(search_sap);
    if (idx == -1) {
        printf("\n[NOT FOUND] No student record matches SAP ID: %lld\n", search_sap);
        return;
    }

    printf("\n[FOUND] Record details for SAP ID %lld:\n", search_sap);
    printStudentDetailed(&students[idx]);
}

/* 15. Provide a function to calculate the CGPA of each student by taking the average of available SGPA values */
void calculateAndDisplayAllCGPA(void) {
    int i;
    if (student_count == 0) {
        printf("\n[INFO] No student records available.\n");
        return;
    }

    printf("\n========================================================================================\n");
    printf("               STUDENT CGPA CALCULATION REPORT (Average of Available SGPAs)              \n");
    printf("========================================================================================\n");
    printf("%-12s %-14s %-22s %-6s %-16s %-8s\n", "SAP ID", "Roll No", "Name", "Year", "Completed Sems", "CGPA");
    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < student_count; i++) {
        int avail = getAvailableSGPACount(&students[i]);
        float cgpa = calculateCGPA(&students[i]);
        printf("%-12lld %-14s %-22s %-6d %-16d %-8.2f\n",
               students[i].sap_id,
               students[i].roll_no,
               students[i].name,
               students[i].year,
               avail,
               cgpa);
    }
    printf("========================================================================================\n");
}

/* 16. Provide a function to calculate the average CGPA of students belonging to each year */
void calculateYearlyAverageCGPA(void) {
    int y, i;
    int year_counts[5] = {0};
    float year_sums[5] = {0.0f};

    if (student_count == 0) {
        printf("\n[INFO] No student records available.\n");
        return;
    }

    for (i = 0; i < student_count; i++) {
        int yr = students[i].year;
        if (yr >= 1 && yr <= 4) {
            year_sums[yr] += calculateCGPA(&students[i]);
            year_counts[yr]++;
        }
    }

    printf("\n=============================================================\n");
    printf("           ACADEMIC YEAR-WISE AVERAGE CGPA REPORT            \n");
    printf("=============================================================\n");
    printf("%-12s %-18s %-16s\n", "Academic Year", "Student Count", "Average CGPA");
    printf("-------------------------------------------------------------\n");

    for (y = 1; y <= 4; y++) {
        const char *yr_label;
        switch (y) {
            case 1: yr_label = "1st Year"; break;
            case 2: yr_label = "2nd Year"; break;
            case 3: yr_label = "3rd Year"; break;
            case 4: yr_label = "4th Year"; break;
            default: yr_label = "Unknown"; break;
        }

        if (year_counts[y] > 0) {
            float avg = year_sums[y] / (float)year_counts[y];
            printf("%-12s %-18d %-16.2f\n", yr_label, year_counts[y], avg);
        } else {
            printf("%-12s %-18d %-16s\n", yr_label, 0, "N/A (No records)");
        }
    }
    printf("=============================================================\n");
}

/* 17. Provide a function to display the records of all students */
void displayAllStudents(void) {
    int i;
    if (student_count == 0) {
        printf("\n[INFO] No student records currently in database.\n");
        return;
    }

    printf("\nTotal Students: %d\n", student_count);
    printTableHeader();
    for (i = 0; i < student_count; i++) {
        printStudentTableRow(&students[i]);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

/* 18. Provide a function to delete an individual student record */
void deleteStudent(void) {
    long long del_sap;
    int idx, i;
    char confirm[10];

    if (student_count == 0) {
        printf("\n[INFO] No student records to delete.\n");
        return;
    }

    printf("\n--- DELETE STUDENT RECORD ---\n");
    printf("Enter SAP ID of the student to delete: ");
    if (!readLongLong(&del_sap)) {
        printf("[ERROR] Invalid SAP ID format.\n");
        return;
    }

    idx = findStudentIndexBySAP(del_sap);
    if (idx == -1) {
        printf("[ERROR] Record with SAP ID %lld not found. Deletion cancelled.\n", del_sap);
        return;
    }

    printf("Found student: %s (SAP ID: %lld, Roll No: %s)\n",
           students[idx].name, students[idx].sap_id, students[idx].roll_no);
    printf("Are you sure you want to permanently delete this record? (y/n): ");
    readLine(confirm, sizeof(confirm));
    if (confirm[0] != 'y' && confirm[0] != 'Y') {
        printf("[INFO] Deletion cancelled by user.\n");
        return;
    }

    /* Shift remaining elements */
    for (i = idx; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;

    printf("[SUCCESS] Student record with SAP ID %lld successfully removed.\n", del_sap);
    printf("Remaining students in database: %d\n", student_count);
}

/* 19. Provide a function to display all student records in increasing order of SAP ID */
void displaySortedBySAP(void) {
    Student temp[MAX_STUDENTS];
    int i, j;

    if (student_count == 0) {
        printf("\n[INFO] No records available to display.\n");
        return;
    }

    /* Make a copy to preserve original insertion ordering */
    for (i = 0; i < student_count; i++) {
        temp[i] = students[i];
    }

    /* Bubble Sort in increasing order of SAP ID */
    for (i = 0; i < student_count - 1; i++) {
        for (j = 0; j < student_count - i - 1; j++) {
            if (temp[j].sap_id > temp[j + 1].sap_id) {
                Student swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    printf("\n========================================================================================================================\n");
    printf("                                STUDENT RECORDS SORTED BY SAP ID (INCREASING ORDER)                                     \n");
    printf("========================================================================================================================\n");
    printTableHeader();
    for (i = 0; i < student_count; i++) {
        printStudentTableRow(&temp[i]);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

/* 20. Provide a function to display all student records in increasing order of Name */
void displaySortedByName(void) {
    Student temp[MAX_STUDENTS];
    int i, j;

    if (student_count == 0) {
        printf("\n[INFO] No records available to display.\n");
        return;
    }

    /* Make a copy */
    for (i = 0; i < student_count; i++) {
        temp[i] = students[i];
    }

    /* Bubble Sort in alphabetical order of Name (case-insensitive) */
    for (i = 0; i < student_count - 1; i++) {
        for (j = 0; j < student_count - i - 1; j++) {
            /* Case-insensitive string comparison */
            int cmp = 0;
            const char *p1 = temp[j].name;
            const char *p2 = temp[j + 1].name;
            while (*p1 && *p2) {
                char c1 = (char)tolower((unsigned char)*p1);
                char c2 = (char)tolower((unsigned char)*p2);
                if (c1 != c2) {
                    cmp = c1 - c2;
                    break;
                }
                p1++;
                p2++;
            }
            if (cmp == 0) {
                cmp = (int)strlen(temp[j].name) - (int)strlen(temp[j + 1].name);
            }

            if (cmp > 0) {
                Student swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    printf("\n========================================================================================================================\n");
    printf("                                  STUDENT RECORDS SORTED BY NAME (ALPHABETICAL ORDER)                                   \n");
    printf("========================================================================================================================\n");
    printTableHeader();
    for (i = 0; i < student_count; i++) {
        printStudentTableRow(&temp[i]);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

/* =====================================================================================
 * Part B – AI-Assisted Academic Advisor (Mini Project)
 * Rule-based decision-making system suggested by AI prompt engineering
 * =====================================================================================
 */

/*
 * Categories of Advice:
 * 1. Excellent Performance (CGPA >= 9.0)
 * 2. Good Performance (7.5 <= CGPA < 9.0)
 * 3. Needs Improvement (6.0 <= CGPA < 7.5)
 * 4. Requires Immediate Attention (CGPA < 6.0)
 */
void getAIAdvice(float cgpa, char *category_out, char *advice_out) {
    if (cgpa >= 9.0f) {
        strcpy(category_out, "Excellent Performance");
        strcpy(advice_out,
               "Outstanding academic record! Maintain your current study pattern. "
               "Recommended to engage in research publications, competitive programming, "
               "and target premier tier-1 technical internships.");
    } else if (cgpa >= 7.5f) {
        strcpy(category_out, "Good Performance");
        strcpy(advice_out,
               "Consistent and solid performance. Maintain your regular study schedule, "
               "focus on subjects where SGPA dipped below 8.0, and undertake domain-specific "
               "capstone projects.");
    } else if (cgpa >= 6.0f) {
        strcpy(category_out, "Needs Improvement");
        strcpy(advice_out,
               "Moderate performance. Needs improvement - focus more on core subjects with "
               "lower SGPA, seek faculty mentoring during office hours, and dedicate 2 hours "
               "daily for concept reinforcement.");
    } else {
        strcpy(category_out, "Requires Immediate Attention");
        strcpy(advice_out,
               "Academic warning zone. Requires immediate attention - consult your academic "
               "counselor, enroll in peer-assisted remedial classes, solve previous years' "
               "question papers, and rebuild foundational concepts.");
    }
}

/* Interactive Academic Advisor Menu Option */
void runAcademicAdvisor(void) {
    long long sap;
    int idx;
    char category[50];
    char advice[256];
    float cgpa;

    if (student_count == 0) {
        printf("\n[INFO] No students available in system.\n");
        return;
    }

    printf("\n=============================================================\n");
    printf("              AI-ASSISTED ACADEMIC ADVISOR                   \n");
    printf("=============================================================\n");
    printf("Enter Student SAP ID to generate personalized advice: ");
    if (!readLongLong(&sap)) {
        printf("[ERROR] Invalid SAP ID format.\n");
        return;
    }

    idx = findStudentIndexBySAP(sap);
    if (idx == -1) {
        printf("[NOT FOUND] No record matches SAP ID: %lld\n", sap);
        return;
    }

    cgpa = calculateCGPA(&students[idx]);
    getAIAdvice(cgpa, category, advice);

    printf("\n------------------- ADVISORY REPORT -------------------------\n");
    printf("Student Name    : %s\n", students[idx].name);
    printf("SAP ID          : %lld\n", students[idx].sap_id);
    printf("Roll Number     : %s\n", students[idx].roll_no);
    printf("Year / Semester : Year %d, Semester %d\n", students[idx].year, students[idx].semester);
    printf("Calculated CGPA : %.2f\n", cgpa);
    printf("Performance Tier: [%s]\n", category);
    printf("AI Recommendation:\n  \"%s\"\n", advice);
    printf("-------------------------------------------------------------\n");
}

/* 25. Demonstration of at least 3 distinct CGPA cases as mandated by assignment instructions */
void printAdvisorDemoCases(void) {
    float test_cases[4] = {9.40f, 8.30f, 7.02f, 5.40f};
    char category[50];
    char advice[256];
    int i;

    printf("\n========================================================================================\n");
    printf("            AI-ASSISTED ACADEMIC ADVISOR - MULTI-CASE DEMONSTRATION                     \n");
    printf("         (Verifying Decision-Making Function Across Different CGPA Tiers)              \n");
    printf("========================================================================================\n");

    for (i = 0; i < 4; i++) {
        getAIAdvice(test_cases[i], category, advice);
        printf("\n[Case %d] Tested CGPA: %.2f\n", i + 1, test_cases[i]);
        printf("  Category      : %s\n", category);
        printf("  Recommendation: %s\n", advice);
    }
    printf("========================================================================================\n");
}

/* =====================================================================================
 * Display Formatting Functions
 * =====================================================================================
 */
void printTableHeader(void) {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-20s %-12s %-32s %-5s %-5s %-6s\n",
           "SAP ID", "Roll No", "Name", "Phone", "Email", "Year", "Sem", "CGPA");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

void printStudentTableRow(const Student *s) {
    printf("%-12lld %-12s %-20s %-12s %-32s %-5d %-5d %-6.2f\n",
           s->sap_id,
           s->roll_no,
           s->name,
           s->phone_no,
           s->email_id,
           s->year,
           s->semester,
           calculateCGPA(s));
}

void printStudentDetailed(const Student *s) {
    int i;
    char category[50];
    char advice[256];
    float cgpa = calculateCGPA(s);
    getAIAdvice(cgpa, category, advice);

    printf("-------------------------------------------------------------\n");
    printf("SAP ID          : %lld\n", s->sap_id);
    printf("Roll Number     : %s\n", s->roll_no);
    printf("Full Name       : %s\n", s->name);
    printf("Contact Phone   : %s\n", s->phone_no);
    printf("Email Address   : %s\n", s->email_id);
    printf("Academic Year   : Year %d\n", s->year);
    printf("Current Semester: Semester %d\n", s->semester);
    printf("Semester SGPAs  :\n");
    for (i = 0; i < NUM_SEMESTERS; i++) {
        if (s->sgpa[i] >= 0.0f) {
            printf("  Sem %d: %.2f", i + 1, s->sgpa[i]);
        } else {
            printf("  Sem %d: [N/A]", i + 1);
        }
        if ((i + 1) % 4 == 0) printf("\n");
        else printf("  |  ");
    }
    printf("\nCalculated CGPA : %.2f\n", cgpa);
    printf("Academic Status : %s\n", category);
    printf("AI Recommendation:\n  %s\n", advice);
    printf("-------------------------------------------------------------\n");
}
