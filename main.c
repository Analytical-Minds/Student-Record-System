#include "main.h"

/*
 * the student record program allows a user
 * to enter numerous student details and perform
 * various CRUD functions
 * 
 * return - 0 (success)
*/

int main() {
    char user[50];

    printf("Hello! Welcome to the Students Score Record program.\nPlease enter your name: ");
    do {
        cleanStringInput(user);
        if (cleanStringInput(user)) {
            printf("Invalid input! Please enter a valid name: ");
        }
    } while (cleanStringInput(user));

    printf("Welcome %s! Kindly select an operation from the functions below.\nProvide the number of the operation you would like to perform\n", user);

    int choice;
    int studentCount = 0;
    int capacity = INITIAL_CAPACITY;
    struct BSTNode* bstRoot = NULL;
    struct student *students = (struct student *)malloc(capacity * sizeof(struct student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        do {
            char input[20];
            fgets(input, sizeof(input), stdin);
            if (cleanNumericInput(input)) {
                printf("Invalid choice! Please enter a valid number: ");
            } else {
                choice = atoi(input);
            }
        } while (choice < 1 || choice > 10);

        switch (choice) {
            case 1:
                displayAllStudents(students, studentCount);
                break;
            case 2:
                addStudent(&students, &studentCount, &capacity);
                bstRoot = insertIntoBST(bstRoot, students[studentCount - 1]);
                break;
            case 3:
                modifyStudent(students, studentCount);
                break;
            case 4:
                deleteStudent(students, &studentCount);
                break;
            case 5:
                printf("Enter roll number to search: ");
                int rollNumber;
                do {
                    char input[20];
                    fgets(input, sizeof(input), stdin);
                    if (cleanNumericInput(input)) {
                        printf("Invalid roll number! Please enter a valid number: ");
                    } else {
                        rollNumber = atoi(input);
                    }
                } while (rollNumber <= 0);
                struct student* foundStudent = searchBST(bstRoot, rollNumber);
                if (foundStudent) {
                    printf("\nStudent found:\n");
                    displayStudentData(foundStudent);
                } else {
                    printf("Student with Roll Number %d not found.\n", rollNumber);
                }
                break;
            case 6:
                if (studentCount == 0) {
                    printf("No students available.\n");
                    break;
                }
                for (int i = 0; i < studentCount; i++) {
                    float sum = 0;
                    for (int j = 0; j < students[i].num_scores; j++) {
                        sum += students[i].marks[j];
                    }
                    students[i].average_score = (students[i].num_scores > 0) ? (sum / students[i].num_scores) : 0;
                }
                printf("\nStudents with computed average scores:\n");
                displayAverageScore(students, studentCount);
                break;
            case 7:
                if (studentCount == 0) {
                    printf("No students to sort.\n");
                    break;
                }
                printf("Choose sorting order:\n");
                printf("1. Ascending (Lowest Average First)\n");
                printf("2. Descending (Highest Average First)\n");
                printf("Enter choice: ");
                int order;
                do {
                    char input[20];
                    fgets(input, sizeof(input), stdin);
                    if (cleanNumericInput(input)) {
                        printf("Invalid choice! Please enter 1 or 2: ");
                    } else {
                        order = atoi(input);
                    }
                } while (order != 1 && order != 2);
                int ascending = (order == 1);
                quickSort(students, 0, studentCount - 1, ascending);
                printf("\nStudents sorted by average score:\n");
                displayAverageScore(students, studentCount);
                break;
            case 8:
                saveStudentsToFile(students, studentCount, "students.txt");
                printf("Student records saved to file.\n");
                break;
            case 9:
                students = loadStudentsFromFile(&studentCount, &capacity, "students.txt");
                if (students != NULL) {
                    printf("Loaded %d student records from file.\n", studentCount);
                    displayAllStudents(students, studentCount);
                    bstRoot = NULL;
                    for (int i = 0; i < studentCount; i++) {
                        bstRoot = insertIntoBST(bstRoot, students[i]);
                    }
                }
                break;
            case 10:
                printf("Exiting the program. Goodbye!\n");
                freeBST(bstRoot);
                for (int i = 0; i < studentCount; i++) {
                    free(students[i].marks);
                }
                free(students);
                return 0;
        }
    }
    return 0;
}