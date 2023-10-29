#ifndef STUDENT_DATABASE_H
#define STUDENT_DATABASE_H

// Include necessary headers
#include <stdio.h>
#include <ctype.h>

// Define the structure for student records
struct student {
    char first_name[20];
    char last_name[20];
    int gpa;
    char grade[10];
    char city[20];
    float per;
};

// Function prototypes
void addStudent();
void studentRecord();
void searchStudent();
void deleteRecord();

#endif // STUDENT_DATABASE_H
