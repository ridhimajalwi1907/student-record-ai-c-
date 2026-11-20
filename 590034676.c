/*
 * =====================================================================================
 * Project Title : AI-Assisted Student Record and Result Management System
 * Course Code   : PRC1001 (Programming in C)
 * Program       : B. Tech CSE - Semester I
 * Institution   : University of Petroleum and Energy Studies (UPES)
 * Student Name  : Ridhima Jalwi
 * SAP ID        : 590034676
 * =====================================================================================
 * Commit 2: Student record management functions (add, search, display, delete)
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

typedef struct {
    long long sap_id;
    char roll_no[30];
    char name[60];
    char phone_no[20];
    char email_id[60];
    int year;
    int semester;
    float sgpa[NUM_SEMESTERS];
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void readLine(char *buffer, int size);
int readInt(int *out);
float readFloat(float *out);
long long readLongLong(long long *out);
void initializeDefaultRecords(void);
int findStudentIndexBySAP(long long sap_id);

void addStudent(void);
void searchStudent(void);
void displayAllStudents(void);
void deleteStudent(void);
void printTableHeader(void);
void printStudentTableRow(const Student *s);

int main(void) {
    int choice = 0;
    initializeDefaultRecords();

    printf("\n======================================================================\n");
    printf("   UNIVERSITY OF PETROLEUM AND ENERGY STUDIES (UPES)\n");
    printf("   PRC1001: Programming in C - Project-Based Assignment\n");
    printf("   Project: AI-Assisted Student Record & Result Management System\n");
    printf("   Author SAP ID: 590034676\n");
    printf("======================================================================\n");

    while (1) {
        printf("\n------------- MAIN MENU -------------\n");
        printf(" 1. Add Student Details\n");
        printf(" 2. Search and Display Student Record\n");
        printf(" 3. Calculate CGPA of All Students\n");
        printf(" 4. Calculate Average CGPA for Each Academic Year\n");
        printf(" 5. Display Records of All Students\n");
        printf(" 6. Delete an Individual Student Record\n");
        printf(" 7. Display All Records in Increasing Order of SAP ID\n");
        printf(" 8. Display All Records in Increasing Order of Name\n");
        printf(" 9. AI-Assisted Academic Advisor\n");
        printf(" 10. AI Advisor Demonstration\n");
        printf(" 11. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice (1-11): ");

        if (!readInt(&choice)) {
            printf("[ERROR] Invalid input.\n");
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: printf("[INFO] CGPA calculation module in progress.\n"); break;
            case 4: printf("[INFO] Yearly average module in progress.\n"); break;
            case 5: displayAllStudents(); break;
            case 6: deleteStudent(); break;
            case 7: printf("[INFO] SAP sorting module in progress.\n"); break;
            case 8: printf("[INFO] Name sorting module in progress.\n"); break;
            case 9: printf("[INFO] AI advisor module in progress.\n"); break;
            case 10: printf("[INFO] AI demo module in progress.\n"); break;
            case 11:
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("[ERROR] Invalid choice.\n");
                break;
        }
    }
    return 0;
}

void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\r') buffer[len - 1] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

int readInt(int *out) {
    char buf[128];
    char *endptr;
    readLine(buf, sizeof(buf));
    if (strlen(buf) == 0) return 0;
    *out = (int)strtol(buf, &endptr, 10);
    return (endptr != buf);
}

float readFloat(float *out) {
    char buf[128];
    char *endptr;
    readLine(buf, sizeof(buf));
    if (strlen(buf) == 0) return 0;
    *out = (float)strtod(buf, &endptr);
    return (endptr != buf);
}

long long readLongLong(long long *out) {
    char buf[128];
    char *endptr;
    readLine(buf, sizeof(buf));
    if (strlen(buf) == 0) return 0;
    *out = (long long)strtoll(buf, &endptr, 10);
    return (endptr != buf);
}

int findStudentIndexBySAP(long long sap_id) {
    int i;
    for (i = 0; i < student_count; i++) {
        if (students[i].sap_id == sap_id) return i;
    }
    return -1;
}

void addStudent(void) {
    Student s;
    int completed_sems = 0, i;
    if (student_count >= MAX_STUDENTS) {
        printf("[ERROR] Database full.\n");
        return;
    }

    printf("\n--- ADD NEW STUDENT RECORD ---\n");
    printf("Enter SAP ID: ");
    if (!readLongLong(&s.sap_id) || s.sap_id <= 0) {
        printf("[ERROR] Invalid SAP ID.\n");
        return;
    }
    if (findStudentIndexBySAP(s.sap_id) != -1) {
        printf("[ERROR] Student already exists.\n");
        return;
    }

    printf("Enter Roll Number: ");
    readLine(s.roll_no, sizeof(s.roll_no));
    printf("Enter Full Name: ");
    readLine(s.name, sizeof(s.name));
    printf("Enter Phone Number: ");
    readLine(s.phone_no, sizeof(s.phone_no));
    printf("Enter Email ID: ");
    readLine(s.email_id, sizeof(s.email_id));
    printf("Enter Academic Year (1-4): ");
    readInt(&s.year);
    printf("Enter Current Semester (1-8): ");
    readInt(&s.semester);

    for (i = 0; i < NUM_SEMESTERS; i++) s.sgpa[i] = -1.0f;

    printf("Enter completed semesters (0 to %d): ", s.semester);
    readInt(&completed_sems);
    for (i = 0; i < completed_sems; i++) {
        printf("  Enter SGPA for Semester %d: ", i + 1);
        readFloat(&s.sgpa[i]);
    }

    students[student_count++] = s;
    printf("[SUCCESS] Student '%s' added successfully.\n", s.name);
}

void searchStudent(void) {
    long long sap;
    int idx;
    printf("\nEnter SAP ID to search: ");
    readLongLong(&sap);
    idx = findStudentIndexBySAP(sap);
    if (idx == -1) {
        printf("[NOT FOUND] No record for SAP ID %lld\n", sap);
        return;
    }
    printf("\nFound: %s (SAP: %lld, Roll: %s, Year: %d, Sem: %d)\n",
           students[idx].name, students[idx].sap_id, students[idx].roll_no,
           students[idx].year, students[idx].semester);
}

void deleteStudent(void) {
    long long sap;
    int idx, i;
    char confirm[10];
    printf("\nEnter SAP ID to delete: ");
    readLongLong(&sap);
    idx = findStudentIndexBySAP(sap);
    if (idx == -1) {
        printf("[ERROR] SAP ID %lld not found.\n", sap);
        return;
    }
    printf("Delete %s? (y/n): ", students[idx].name);
    readLine(confirm, sizeof(confirm));
    if (confirm[0] == 'y' || confirm[0] == 'Y') {
        for (i = idx; i < student_count - 1; i++) students[i] = students[i + 1];
        student_count--;
        printf("[SUCCESS] Student deleted.\n");
    }
}

void printTableHeader(void) {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-20s %-12s %-28s %-5s %-5s\n",
           "SAP ID", "Roll No", "Name", "Phone", "Email", "Year", "Sem");
    printf("----------------------------------------------------------------------------------------------------\n");
}

void printStudentTableRow(const Student *s) {
    printf("%-12lld %-12s %-20s %-12s %-28s %-5d %-5d\n",
           s->sap_id, s->roll_no, s->name, s->phone_no, s->email_id, s->year, s->semester);
}

void displayAllStudents(void) {
    int i;
    printf("\nTotal Students: %d\n", student_count);
    printTableHeader();
    for (i = 0; i < student_count; i++) printStudentTableRow(&students[i]);
    printf("----------------------------------------------------------------------------------------------------\n");
}

void initializeDefaultRecords(void) {
    int i, j;
    student_count = INITIAL_STUDENT_COUNT;
    for (i = 0; i < MAX_STUDENTS; i++)
        for (j = 0; j < NUM_SEMESTERS; j++)
            students[i].sgpa[j] = -1.0f;

    students[0].sap_id = 590034676LL;
    strcpy(students[0].roll_no, "R214223001");
    strcpy(students[0].name, "Ridhima Jalwi");
    strcpy(students[0].phone_no, "9876543210");
    strcpy(students[0].email_id, "ridhima.590034676@stu.upes.ac.in");
    students[0].year = 1;
    students[0].semester = 1;
    students[0].sgpa[0] = 9.40f;

    students[1].sap_id = 590034102LL;
    strcpy(students[1].roll_no, "R214223045");
    strcpy(students[1].name, "Aarav Sharma");
    strcpy(students[1].phone_no, "9811223344");
    strcpy(students[1].email_id, "aarav.sharma@stu.upes.ac.in");
    students[1].year = 2;
    students[1].semester = 3;
    students[1].sgpa[0] = 8.20f;
    students[1].sgpa[1] = 8.40f;

    students[2].sap_id = 590034215LL;
    strcpy(students[2].roll_no, "R214223089");
    strcpy(students[2].name, "Ananya Verma");
    strcpy(students[2].phone_no, "9822334455");
    strcpy(students[2].email_id, "ananya.verma@stu.upes.ac.in");
    students[2].year = 3;
    students[2].semester = 5;
    students[2].sgpa[0] = 7.00f;
    students[2].sgpa[1] = 7.20f;

    students[3].sap_id = 590034330LL;
    strcpy(students[3].roll_no, "R214223120");
    strcpy(students[3].name, "Rohan Gupta");
    strcpy(students[3].phone_no, "9833445566");
    strcpy(students[3].email_id, "rohan.gupta@stu.upes.ac.in");
    students[3].year = 1;
    students[3].semester = 2;
    students[3].sgpa[0] = 5.40f;

    students[4].sap_id = 590034450LL;
    strcpy(students[4].roll_no, "R214223155");
    strcpy(students[4].name, "Diya Patel");
    strcpy(students[4].phone_no, "9844556677");
    strcpy(students[4].email_id, "diya.patel@stu.upes.ac.in");
    students[4].year = 4;
    students[4].semester = 7;
    students[4].sgpa[0] = 8.80f;
    students[4].sgpa[1] = 9.10f;
}
