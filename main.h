// main.h
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INITIAL_CAPACITY 10 // Initial capacity for the dynamic array
#define MAX_SCORES 15       // Maximum number of scores per student

/**
 * struct student - the data for the student
 * name: the student's name
 * roll_number: the student's roll number
 * num_scores: number of scores to be entered for student
 * marks: pointer to the array storing the student scores
*/
struct student {
    char name[50];
    int roll_number;
    float *marks; // Pointer to the dynamically allocated array
    int num_scores; // Number of scores entered
    float average_score; // store average score of student
};


/**
 * BST (Binary search tree) Node
 *
*/
struct BSTNode {
    struct student data;
    struct BSTNode* left;
    struct BSTNode* right;
};

// Function prototypes
void displayMenu();
void displayStudentData(const struct student *s);
void inputStudentData(struct student *s);
void displayAllStudents(const struct student students[], int count);
void addStudent(struct student **students, int *count, int *capacity);
void modifyStudent(struct student students[], int count);
void deleteStudent(struct student students[], int *count);
void displayAverageScore(const struct student students[], int count);
void saveStudentsToFile(const struct student students[], int count, const char *filename);
struct student *loadStudentsFromFile(int *count, int *capacity, const char *filename);
struct BSTNode* insertIntoBST(struct BSTNode* root, struct student s);
struct student* searchBST(struct BSTNode* root, int roll_number);
void freeBST(struct BSTNode* root);
void quickSort(struct student students[], int low, int high, int ascending);
int partition(struct student students[], int low, int high, int ascending);
void clearInputBuffer();

#endif // MAIN_H