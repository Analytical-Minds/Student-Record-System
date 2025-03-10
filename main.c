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
    fgets(user, sizeof(user), stdin); // Get user name from stdin

    // Remove the newline character if present
    if (user[strlen(user) - 1] == '\n') {
        user[strlen(user) - 1] = '\0';
    }

    printf("Welcome %s! Kindly select an operation from the functions below.\nProvide the number of the operation you would like perform", user);

    // initialize variables
    int choice;
    int studentCount = 0; // Number of students currently stored
    int capacity = INITIAL_CAPACITY; // Initial capacity of the dynamic array
    struct BSTNode* bstRoot = NULL;  // Root of the BST

    
    // Allocate memory for the dynamic array
    struct student *students = (struct student *)malloc(capacity * sizeof(struct student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1) { // Infinite loop to keep the loop running
        displayMenu(); // Display the menu options
        printf("Enter your choice: ");
        scanf("%d", &choice); // Get user input
        clearInputBuffer(); // Clear the input buffer after scanf

        switch (choice) {
            case 1:
                displayAllStudents(students, studentCount); // Display all students
                break;
            case 2:
                addStudent(&students, &studentCount, &capacity); // Add a new student
                bstRoot = insertIntoBST(bstRoot, students[studentCount - 1]); // Inserting a student into BST
                break;
            case 3:
                modifyStudent(students, studentCount); // Modify a student
                break;
            case 4:
                deleteStudent(students, &studentCount); // Delete a student
                break;
            case 5:
                printf("Enter roll number to search: ");
                int rollNumber;
                scanf("%d", &rollNumber);
                clearInputBuffer();
            
                struct student* foundStudent = searchBST(bstRoot, rollNumber); // search for student record by roll number
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
                int order;
                printf("Choose sorting order:\n");
                printf("1. Ascending (Lowest Average First)\n");
                printf("2. Descending (Highest Average First)\n");
                printf("Enter choice: ");
                scanf("%d", &order);
                clearInputBuffer();
            
                int ascending = (order == 1);
                quickSort(students, 0, studentCount - 1, ascending);
                
                printf("\nStudents sorted by average score:\n");
                displayAverageScore(students, studentCount);
                break;
            case 8:
                saveStudentsToFile(students, studentCount, "students.txt"); // Save students to file
                printf("Student records saved to file.\n");
                break;
            case 9:
                students = loadStudentsFromFile(&studentCount, &capacity, "students.txt"); // Load students from file
                if (students != NULL) {
                    printf("Loaded %d student records from file.\n", studentCount);
                    displayAllStudents(students, studentCount); // Display loaded records

                    // Insert loaded students into the BST
                    bstRoot = NULL; // Clear previous BST
                    for (int i = 0; i < studentCount; i++) {
                        bstRoot = insertIntoBST(bstRoot, students[i]);
                    }
                }
                break;
            case 10:
                printf("Exiting the program. Goodbye!\n");

                freeBST(bstRoot); // free BST Nodes
                
                // Free dynamically allocated memory for each student
                for (int i = 0; i < studentCount; i++) {
                    free(students[i].marks);
                }
                free(students); // Free the dynamic array

                return 0; // Exit the program
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}