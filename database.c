#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>

void add();
void view();
void search();
void del();
void modify();

struct student{
    char firstname[20];
    char lastname[20];
    int roll;
    char course[10];
    float cgpa;
};

void main(){
    int choice=0;
    
    while (choice!=6){
        printf("STUDENT RECORD MANAGEMENT SYSTEM\n\n");
        printf("1. Add student record. \n");
        printf("2. View all student records. \n");
        printf("3. Search student record. \n");
        printf("4. Delete student record. \n");
        printf("5. Modify student record. \n");
        printf("6. Exit\n");
        printf("------------------------------------\n");
        printf("Enter operation: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                system("cls");
                add(); //Add student's record
                system("cls");
                break;
            case 2: 
                system("cls");
                view(); //View all students' record
                printf("Enter any key to exit; \n");
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                search(); //Search a student's record in database
                printf("Enter any key to exit; \n");
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                del(); //Delete a student's record from database
                printf("Enter any key to exit; \n");
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                modify(); //Update a student's record
                printf("Enter any key to exit; \n");
                getch();
                system("cls");
                break;
            case 6:
                system("cls");
                printf("Thank you for using the record management system.\n");
                exit(0);
                break;
            default:
                system("cls");
                printf("Invalid choice.\n");
                break;

        }
    }
}

void add(){
    char c;
    FILE *f;
    struct student info;
    do{
        system("cls");
        printf("ADD STUDENT RECORD\n\n");
        f=fopen("record.txt","ab");
        printf("Enter first name : ");
        scanf("%s",info.firstname);
        printf("Enter last name : ");
        scanf("%s",info.lastname);
        printf("Enter roll number : ");
        scanf("%d",&info.roll);
        printf("Enter course : ");
        scanf("%s",info.course);
        printf("Enter CGPA : ");
        scanf("%f",&info.cgpa);
        printf("-------------------------------\n");
        if (f==NULL){
            fprintf(stderr,"Can't open file\n");
        }else{
            printf("Record entered successfully.\n");
        }
        fwrite(&info,sizeof(struct student),1,f);
        fclose(f);
        printf("\n Do you want to add another record? (y/n : )");
        scanf(" %c",&c);
    }while (c=='Y'|| c=='y');
}

void view(){
    FILE *f;
    struct student info;
    f=fopen("record.txt","rb");
    printf("STUDENT RECORDS\n\n");
    if (f==NULL){
            fprintf(stderr,"Can't open file\n");
    }else{
        printf("Records\n----------------------\n");
    }
    while(fread(&info,sizeof(struct student),1,f)){
        printf("\n Student name : %s %s",info.firstname,info.lastname);
        printf("\n Roll number : %d",info.roll);
        printf("\n Course : %s",info.course);
        printf("\n CGPA : %.2f",info.cgpa);
        printf("\n----------------------------------\n");
    }
    fclose(f);
    getch();
}

void search(){
    FILE *f;
    struct student info;
    f=fopen("record.txt","rb");
    int rollno,found=0;
    printf("\n SEARCH STUDENT\n");
    printf("Enter roll number to search : ");
    scanf("%d",&rollno);
    while (fread(&info,sizeof(struct student),1,f)){
        if (info.roll==rollno){
            found+=1;
            printf("\n Student name : %s %s",info.firstname,info.lastname);
            printf("\n Roll number : %d",info.roll);
            printf("\n Course : %s",info.course);
            printf("\n CGPA : %.2f",info.cgpa);
            printf("\n----------------------------------\n");
        }
    }
    if (!found){
        printf("Record not found. \n");
    }
    fclose(f);
    getch();

}

void del(){
    FILE *f, *f1;
    struct student info;
    f=fopen("record.txt","rb");
    f1=fopen("temp.txt","wb");
    int rollno,found=0;
    printf("Delete student record. \n");
    printf("Enter roll number to delete : ");
    scanf("%d",&rollno);
    if (f==NULL){
        fprintf(stderr,"Can't open file\n");
    }
    while (fread(&info,sizeof(struct student),1,f)){
        if (info.roll==rollno){
            found+=1;
        }else{
            fwrite(&info,sizeof(struct student),1,f1);
        }
    }
    fclose(f);
    fclose(f1);
    
    if (found){
        remove("record.txt");
        rename("temp.txt","record.txt");
        printf("Record deleted successfully. \n");
    }
    if (!found){
        remove("temp.txt");
        printf("Record not found\n");
    }
    getch();    

}

void modify(){
    FILE *f, *f1;
    struct student info;
    f=fopen("record.txt","rb");
    f1=fopen("temp.txt","wb");
    int rollno,found=0;
    printf("Modify student record. \n");
    printf("Enter roll number to modify : ");
    scanf("%d",&rollno);
    if (f==NULL){
        fprintf(stderr,"Can't open file\n");
    }
    while (fread(&info,sizeof(struct student),1,f)){
        if (info.roll==rollno){
            found+=1;
            printf("Enter new details. \n");
            printf("First name : ");
            scanf("%s", info.firstname);
            printf("Last name : ");
            scanf("%s", info.lastname);
            printf("Course : ");
            scanf("%s", info.course);
            printf("CGPA : ");
            scanf("%f", &info.cgpa);
        }
        fwrite(&info,sizeof(struct student),1,f1);
        }
    
    fclose(f);
    fclose(f1);
    
    if (found){
        remove("record.txt");
        rename("temp.txt","record.txt");
        printf("Record modified. \n");
    }
    if (!found){
        remove("temp.txt");
        printf("Record not found\n");
    }
    getch();    
}