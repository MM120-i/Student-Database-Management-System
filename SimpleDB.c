#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "SimpleDB.h"

void addStudent();
void studentRecord();
void searchStudent();
void delete();

struct student{

    char first_name[20];
    char last_name[20];
    int gpa;
    char grade[10];
    char city[20];
    float per;
};


void main() {
    int choice = 0;

    // Main loop to display the menu and process user choices
    while (choice != 5) {  // Continue until the user chooses to exit (option 5)

        // Display the main menu
        printf("\n\t\t\t==========Student Database Management System==========");
        printf("\n\n\n\t\t\t\t 1. Add Student Record\n");
        printf("\t\t\t\t 2. Student Records\n");
        printf("\t\t\t\t 3. Search Student\n");
        printf("\t\t\t\t 4. Delete Record\n");
        printf("\t\t\t\t 5. Exit\n");
        printf("\n\t\t\t ___________________________________________________________\n");
        printf("\t\t\t\t");

        // Read the user's choice
        scanf("%d", &choice);

        switch (choice) {

            case 1:

                system("cls");  // Clear the screen
                addStudent();   // Call the function to add a student record
                system("cls");  // Clear the screen again
                break;

            case 2:

                system("cls");        // Clear the screen
                studentRecord();      // Call the function to display student records
                printf("\t\t\tPress any key to exit\n");
                getch();              // Wait for a key press
                system("cls");        // Clear the screen again
                break;

            case 3:

                system("cls");        // Clear the screen
                searchStudent();      // Call the function to search for a student record
                printf("\n\t\t\t\tPress any key to exit\n");
                getch();              // Wait for a key press
                system("cls");        // Clear the screen again
                break;

            case 4:

                system("cls");  // Clear the screen
                delete(); // Call the function to delete a student record
                printf("\n\t\t\t\tPress any key to exit\n");
                getch();        // Wait for a key press
                system("cls");  // Clear the screen again
                break;

            case 5:

                exit(0);  // Exit the program
                break;

            default:

                printf("\n\t\t\t\tPlease select a valid option (1-5)\n");
                break;
        }
    }
}


void addStudent() {

    char another;
    FILE *fp;
    struct student info;

    do {

        system("cls");  // Clear the screen
        printf("\t\t\t\t==========Add Student Information==========\n\n\n");
        fp = fopen("studentInfo", "a");  // Open the file for appending

        // Input student information
        printf("\n\t\t\tEnter first name   : ");
        scanf("%s", &info.first_name); 

        printf("\n\t\t\tEnter last name    : ");
        scanf("%s", &info.last_name);

        printf("\n\t\t\tEnter GPA         : ");
        scanf("%d", &info.gpa);

        printf("\n\t\t\tEnter grade       : ");
        scanf("%s", &info.grade);

        printf("\n\t\t\tEnter address     : ");
        scanf("%s", &info.city);

        printf("\n\t\t\tEnter percentage  : ");
        scanf("%f", &info.per);

        printf("\n\t\t\t___________________________________\n");

        // Check if the file was opened successfully
        if (fp == NULL) {
            
            fprintf(stderr, "\t\t\tCannot open file\n");  // Display an error message
        } 
        else {

            printf("\t\t\tRecord stored successfully");  // Display a success message
        }

        // Write the student information to the file
        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);  // Close the file

        // Prompt to add another record
        printf("\t\t\t\nDo you want to add another record? (Y/N): ");
        scanf("%s", &another);
        another = toupper(another);  // Convert the response to uppercase

    } while (another == 'Y');  // Repeat if the user wants to add another record
}


void studentRecord() {

    FILE *fp;
    struct student info;
    fp = fopen("studentInfo", "r");  // Open the file for reading

    printf("\t\t\t\t========== Student Records ==========\n\n\n");

    // Check if the file was opened successfully
    if (fp == NULL) {

        fprintf(stderr, "\t\t\tCannot open\n");  // Display an error message
    } else {

        printf("\t\t\t\tRecords\n");
        printf("\t\t\t\t__________________\n\n");
    }

    while (fread(&info, sizeof(struct student), 1, fp)) {

        // Display student information
        printf("\n\t\t\t\tStudent name   : %s %s", info.first_name, info.last_name);
        printf("\n\t\t\t\tGPA            : %d", info.gpa);
        printf("\n\t\t\t\tGrade          : %s", info.grade);
        printf("\n\t\t\t\tAddress        : %s", info.city);
        printf("\n\t\t\t\tPercentage     : %0.2f", info.per);
        printf("\n\t\t\t\t_____________________________________________\n");
    }

    fclose(fp);  // Close the file
    getch();     // Wait for a key press before returning
}


void searchStudent() {

    FILE *fp;
    struct student info;
    int gpa, found = 0;
    fp = fopen("studentInfo", "r");  // Open the file for reading

    printf("\t\t\t\t========== Search Student ==========\n\n\n");
    printf("\t\t\tEnter GPA: ");
    scanf("%d", &gpa);

    while (fread(&info, sizeof(struct student), 1, fp)) {

        // Check if the GPA matches the search criteria
        if (info.gpa == gpa) {

            found = 1;
            // Display student information
            printf("\n\t\t\t\tStudent name   : %s %s", info.first_name, info.last_name);
            printf("\n\t\t\t\tGPA            : %d", info.gpa);
            printf("\n\t\t\t\tGrade          : %s", info.grade);
            printf("\n\t\t\t\tAddress        : %s", info.city);
            printf("\n\t\t\t\tPercentage     : %0.2f", info.per);
            printf("\n\t\t\t\t_____________________________________________\n");
        }
    }

    if (!found) {

        // Display a message if no matching records were found
        printf("\t\t\tRecord not found\n");
    }

    fclose(fp);  // Close the file
    getch();     // Wait for a key press before returning
}


void delete() {

    FILE *fp, *fp1;
    struct student info;
    int gpa, found = 0;

    printf("\t\t\t\t========== Delete Student Record ==========\n\n\n");
    printf("\t\t\tEnter GPA: ");
    scanf("%d", &gpa);

    fp = fopen("studentInfo", "r"); // Open the file for reading
    if (fp == NULL) {

        fprintf(stderr, "\t\t\t\tCan't open file\n");
        return;
    }

    fp1 = fopen("temp.txt", "w"); // Open a temporary file for writing
    if (fp1 == NULL) {

        fprintf(stderr, "\t\t\t\tCan't open temporary file\n");
        fclose(fp); // Close the original file before returning
        return;
    }

    while (fread(&info, sizeof(struct student), 1, fp)) {

        // Check if the GPA matches the search criteria
        if (info.gpa == gpa) {

            found = 1;
        } 
        else {

            // Write records that don't match the search criteria to the temporary file
            fwrite(&info, sizeof(struct student), 1, fp1);
        }
    }

    fclose(fp);  // Close the original file
    fclose(fp1); // Close the temporary file

    if (found) {

        // Delete the original file and rename the temporary file to the original file's name
        remove("studentInfo");
        rename("temp.txt", "studentInfo");
        printf("\n\t\t\tRecord deleted successfully\n");
    } else {

        printf("\n\t\t\tRecord not found\n");
    }

    getch(); // Wait for a key press before returning
}

