#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    float mark1, mark2, mark3;
    float total;
};

void addStudent();
void displayStudents();
void generateRankList();

int main()
{
    int choice;

    while (1)
    {
        printf("\n===== STUDENT MARKS MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Student Records\n");
        printf("3. Generate Rank List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            generateRankList();
            break;

        case 4:
            printf("Exiting Program...\n");
            exit(0);

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks of Subject 1: ");
    scanf("%f", &s.mark1);

    printf("Enter Marks of Subject 2: ");
    scanf("%f", &s.mark2);

    printf("Enter Marks of Subject 3: ");
    scanf("%f", &s.mark3);

    s.total = s.mark1 + s.mark2 + s.mark3;

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("Student Record Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("\nRoll Number : %d\n", s.roll);
        printf("Name        : %s\n", s.name);
        printf("Mark 1      : %.2f\n", s.mark1);
        printf("Mark 2      : %.2f\n", s.mark2);
        printf("Mark 3      : %.2f\n", s.mark3);
        printf("Total Marks : %.2f\n", s.total);
    }

    fclose(fp);
}

void generateRankList()
{
    FILE *fp;
    struct Student s[100], temp;
    int count = 0, i, j;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    while (fread(&s[count], sizeof(struct Student), 1, fp))
    {
        count++;
    }

    fclose(fp);

    // Sorting based on total marks (Descending Order)
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (s[i].total < s[j].total)
            {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n===== RANK LIST =====\n");
    printf("Rank\tRoll No\tName\t\tTotal\n");

    for (i = 0; i < count; i++)
    {
        printf("%d\t%d\t%s\t\t%.2f\n",
               i + 1,
               s[i].roll,
               s[i].name,
               s[i].total);
    }
}
