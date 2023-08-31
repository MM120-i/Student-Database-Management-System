#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

void addStudent();
void studentRecord();
void searchStudent();
void delete();

struct student{

    char first_name[20];
    char last_name[20];
    int roll_no;
    char grade[10];
    char city[20];
    float per;
};


void main(){

    int choice = 0;

    while(choice != 5){

        printf("\n\t\t\t==========Student Database Management System==========");
        printf("\n\n\n\t\t\t\t 1. Add Student Record\n");
        printf("\t\t\t\t 2. Student Records\n");
        printf("\t\t\t\t 3. Search Student\n");
        printf("\t\t\t\t 4. Delete Record\n");
        printf("\t\t\t\t 5. Exit\n");
        printf("\n\t\t\t ___________________________________________________________\n");
        printf("\t\t\t\t");
        scanf("%d", &choice);

        switch (choice){

        case 1:
            
            system("cls");
            addStudent();
            system("cls");
            break;

        case 2:

            system("cls");
            studentRecord();
            printf("\t\t\tPress any key to exit\n");    
            getch();
            system("cls");
            break;
        
        case 3:

            system("cls");
            searchStudent();
            printf("\n\t\t\t\tPress any key to exit\n");
            getch();
            system("cls");
            break;

        case 4:

            system("cls");
            delete();
            printf("\n\t\t\t\tPress any key to exit\n");
            getch();
            system("cls");
            break;
        
        case 5:
        
            exit(0);
            break;
        
        default:

            printf("\n\t\t\t\tPlease select a valid option (1-5)");
            break;
        }
    }
}

void addStudent(){

    char another;
    FILE *fp;
    struct student info;

    do{

        system("cls");
        printf("\t\t\t\t==========Add Student Infomation==========\n\n\n");
        fp = fopen("studentInfo", "a");

        printf("\n\t\t\tEnter first name   : ");
        scanf("%s", &info.first_name); 

        printf("\n\t\t\tEnter last name    : ");
        scanf("%s", &info.last_name);

        printf("\n\t\t\tEnter roll number  : ");
        scanf("%d", &info.roll_no);

        printf("\n\t\t\tEnter grade        : ");
        scanf("%s", &info.grade);

        printf("\n\t\t\tEnter address      : ");
        scanf("%s", &info.city);

        printf("\n\t\t\tEnter percentage   : ");
        scanf("%f", &info.per);

        printf("\n\t\t\t___________________________________\n");

        if(fp == NULL){
            fprintf(stderr, "\t\t\tCannot open file\n");
        }
        else{
            printf("\t\t\tRecord stored successfully");
        }

        fwrite(&info,sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\t\t\t\nDo you want to add another record? (Y/N): ");
        scanf("%s", &another);
        another = toupper(another);
        
    } while (another == 'Y');
    
}

void studentRecord(){

    FILE *fp;
    struct student info;
    fp = fopen("studentInfo", "r");

    printf("\t\t\t\t========== Student Records ==========\n\n\n");

    if(fp == NULL){
        fprintf(stderr, "\t\t\tCannot open\n");
    }
    else{
        printf("\t\t\t\tRecords\n");
        printf("\t\t\t\t__________________\n\n");
    }

    while(fread(&info, sizeof(struct student), 1, fp)){
        
        printf("\n\t\t\t\tStudent name   : %s %s", info.first_name, info.last_name);
        printf("\n\t\t\t\tRoll no        : %d", info.roll_no);
        printf("\n\t\t\t\tGrade          : %s", info.grade);
        printf("\n\t\t\t\tAdderess       : %s", info.city);
        printf("\n\t\t\t\tPercentage     : %0.2f", info.per);
        printf("\n\t\t\t\t_____________________________________________\n");
    }

    fclose(fp);
    getch();
}

void searchStudent(){

    FILE *fp;
    struct student info;
    int roll_no, found = 0;
    fp = fopen("studentInfo", "r");

    printf("\t\t\t\t========== Search Student ==========\n\n\n");
    printf("\t\t\tEnter roll no: ");
    scanf("%d", &roll_no);

    while(fread(&info, sizeof(struct student), 1, fp)){

        if(info.roll_no == roll_no){

            found = 1;
            printf("\n\t\t\t\tStudent name   : %s %s", info.first_name, info.last_name);
            printf("\n\t\t\t\tRoll no        : %d", info.roll_no);
            printf("\n\t\t\t\tGrade          : %s", info.grade);
            printf("\n\t\t\t\tAdderess       : %s", info.city);
            printf("\n\t\t\t\tPercentage     : %0.2f", info.per);
            printf("\n\t\t\t\t_____________________________________________\n");
        }
    }

    if(!found){
        
        printf("\t\t\tRecord not found\n");
    }

    fclose(fp);
    getch();
}

void delete() {

    FILE *fp, *fp1;
    struct student info;
    int roll_no, found = 0;

    printf("\t\t\t\t========== Delete Student Record ==========\n\n\n");
    printf("\t\t\tEnter roll no: ");
    scanf("%d", &roll_no);

    fp = fopen("studentInfo", "r");
    if (fp == NULL) {

        fprintf(stderr, "\t\t\t\tCan't open file\n");
        return;
    }

    fp1 = fopen("temp.txt", "w");
    if (fp1 == NULL) {

        fprintf(stderr, "\t\t\t\tCan't open temporary file\n");
        fclose(fp); // Close the file before returning
        return;
    }

    while (fread(&info, sizeof(struct student), 1, fp)) {

        if (info.roll_no == roll_no) {
            found = 1;
        } else {
            fwrite(&info, sizeof(struct student), 1, fp1);
        }
    }

    fclose(fp);  // Close the original file
    fclose(fp1); // Close the temporary file

    if (found) {

        remove("studentInfo");
        rename("temp.txt", "studentInfo");
        printf("\n\t\t\tRecord deleted successfully\n");
    } else {
        printf("\n\t\t\tRecord not found\n");
    }

    getch();
}
