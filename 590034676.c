/*
 * =====================================================================================
 * Project Title : AI-Assisted Student Record and Result Management System
 * Course Code   : PRC1001 (Programming in C)
 * Program       : B. Tech CSE - Semester I
 * Institution   : University of Petroleum and Energy Studies (UPES)
 * Student Name  : Ridhima Jalwi
 * SAP ID        : 590034676
 * =====================================================================================
 * Commit 1: Initial C program skeleton, data structures, and menu-driven loop
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

/* Student Structure Definition */
typedef struct {
    long long sap_id;           /* UPES SAP ID */
    char roll_no[30];          /* University Roll Number */
    char name[60];             /* Student Full Name */
    char phone_no[20];         /* Contact Phone Number */
    char email_id[60];         /* University / Personal Email ID */
    int year;                  /* Academic Year: 1, 2, 3, or 4 */
    int semester;              /* Current Semester: 1 through 8 */
    float sgpa[NUM_SEMESTERS]; /* SGPA for all 8 semesters (-1.0 if not completed) */
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

/* Helper prototypes */
void readLine(char *buffer, int size);
int readInt(int *out);
float readFloat(float *out);
long long readLongLong(long long *out);
void initializeDefaultRecords(void);

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

        if (choice == 11) {
            printf("Exiting system. Goodbye!\n");
            break;
        } else {
            printf("[INFO] Functionality %d under development.\n", choice);
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

void initializeDefaultRecords(void) {
    int i, j;
    student_count = INITIAL_STUDENT_COUNT;
    for (i = 0; i < MAX_STUDENTS; i++) {
        for (j = 0; j < NUM_SEMESTERS; j++) {
            students[i].sgpa[j] = -1.0f;
        }
    }
    students[0].sap_id = 590034676LL;
    strcpy(students[0].roll_no, "R214223001");
    strcpy(students[0].name, "Ridhima Jalwi");
    strcpy(students[0].phone_no, "9876543210");
    strcpy(students[0].email_id, "ridhima.590034676@stu.upes.ac.in");
    students[0].year = 1;
    students[0].semester = 1;
    students[0].sgpa[0] = 9.40f;
}
