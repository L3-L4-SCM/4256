#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

typedef struct
{
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

void menu();
void addStudent();
void listStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
int studentExists(int id);
void saveStudent(Student s);
Student getStudentById(int id);
void updateFile(Student s, int mode);

// mode 1 = update, 0 = delete

int main() 

{
    menu();
    return 0;
}

void menu() 

{
    int choice;
    do 
    {

      printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. List Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) 
        {

           case 1: addStudent(); break;
            case 2: listStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice.\n");

        }
    } 
 
    while (choice != 6);
}

void addStudent() 

{
    Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);
    getchar();
    
    if (studentExists(s.id)) 
    {
        printf("Student with ID %d already exists.\n", s.id);
        return;
    }

    printf("Enter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &s.age);

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    saveStudent(s);
    printf("Student added successfully.\n");
}

void listStudents() 

{
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) 
    {
        printf("No student records found.\n");
        return;
    }

    Student s;
    printf("\n%-10s %-20s %-10s %-10s\n", "ID", "Name", "Age", "GPA");
    printf("-------------------------------------------------\n");
    while (fread(&s, sizeof(Student), 1, fp)) 
    {
        printf("%-10d %-20s %-10d %-10.2f\n", s.id, s.name, s.age, s.gpa);
    }

    fclose(fp);
}

void searchStudent() 

{
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    if (!studentExists(id)) 
    {
 
      printf("Student with ID %d not found.\n", id);
        return;
    }

    Student s = getStudentById(id);
    printf("\nStudent Details:\n");
    printf("ID   : %d\n", s.id);
    printf("Name : %s\n", s.name);
    printf("Age  : %d\n", s.age);
    printf("GPA  : %.2f\n", s.gpa);
}

void deleteStudent() 

{
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    if (!studentExists(id)) 
    {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    updateFile(getStudentById(id), 0);
    printf("Student deleted successfully.\n");
}

void updateStudent() 

{
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    getchar();

    if (!studentExists(id)) 
    {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    Student s;
    s.id = id;
    printf("Enter new name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter new age: ");
    scanf("%d", &s.age);

    printf("Enter new GPA: ");
    scanf("%f", &s.gpa);

    updateFile(s, 1);
    printf("Student updated successfully.\n");
}

int studentExists(int id) 

{
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return 0;

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) 
    {
        if (s.id == id) 
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

Student getStudentById(int id) 

{
    FILE *fp = fopen(FILE_NAME, "r");
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) 
    {
        
      if (s.id == id) 
        {
            fclose(fp);
            return s;

        }
    }

    fclose(fp);
    // Return empty
    Student empty = {0, "", 0, 0.0};
    return empty;

  }

void saveStudent(Student s) 

{
  
  FILE *fp = fopen(FILE_NAME, "ab");
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
}

void updateFile(Student s, int mode) 

{
    
  FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.txt", "wb");
    Student curr;

    while (fread(&curr, sizeof(Student), 1, fp)) 
    {
        if (curr.id == s.id) 
        {
            if (mode == 1) fwrite(&s, sizeof(Student), 1, temp); 
          
            // update
            // if mode == 0 (delete), do nothing
        
         }
         else 
        {
          
          fwrite(&curr, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

}
