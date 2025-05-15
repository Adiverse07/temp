#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILE_NAME "students.dat"

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

void createStudent();
void readStudents();
void updateStudent();
void deleteStudent();
void menu();

void menu() {
    int choice;

    while (1) {
        printf("\nStudent Database Management System\n");
        printf("1. Add Student (Create)\n");
        printf("2. Display Students (Read)\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: createStudent(); break;
            case 2: readStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void createStudent() {
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    if (write(fd, &s, sizeof(Student)) < 0) {
        perror("Error writing to file");
    } else {
        printf("Student added successfully!\n");
    }

    close(fd);
}

void readStudents() {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0) {
        printf("No student records found.\n");
        return;
    }

    Student s;
    printf("\nRoll\tName\t\tMarks\n");
    printf("--------------------------------\n");

    while (read(fd, &s, sizeof(Student)) == sizeof(Student)) {
        printf("%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }

    close(fd);
}

void updateStudent() {
    int fd = open(FILE_NAME, O_RDWR);
    if (fd < 0) {
        printf("No student records found.\n");
        return;
    }

    int roll, found = 0;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    Student s;
    off_t offset = 0;

    while (read(fd, &s, sizeof(Student)) == sizeof(Student)) {
        if (s.roll == roll) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            lseek(fd, offset, SEEK_SET); // Move back to overwrite
            write(fd, &s, sizeof(Student));
            found = 1;
            break;
        }
        offset += sizeof(Student);
    }

    close(fd);

    if (found)
        printf("Student record updated successfully.\n");
    else
        printf("Student with Roll No. %d not found.\n", roll);
}

void deleteStudent() {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0) {
        printf("No student records found.\n");
        return;
    }

    int tempFd = open("temp.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tempFd < 0) {
        perror("Error creating temp file");
        close(fd);
        return;
    }

    int roll, found = 0;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    Student s;
    while (read(fd, &s, sizeof(Student)) == sizeof(Student)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            write(tempFd, &s, sizeof(Student));
        }
    }

    close(fd);
    close(tempFd);

    unlink(FILE_NAME);                // delete old file
    rename("temp.dat", FILE_NAME);   // rename temp file

    if (found)
        printf("Student record deleted successfully.\n");
    else
        printf("Student with Roll No. %d not found.\n", roll);
}

int main() {
    menu();
    return 0;
}
