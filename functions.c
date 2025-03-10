#include "main.h"

// Function to display the menu
void displayMenu() {
    printf("\n----------- Menu -----------\n");
    printf("1. Display Student Records\n");
    printf("2. Add Student Record\n");
    printf("3. Modify Student Record\n");
    printf("4. Delete Student Record\n");
    printf("5. Search for a Student\n");
    printf("6. Calculate Average Mark\n");
    printf("7. Sort Student Record\n");
    printf("8. Save Record To File\n");
    printf("9. Load Record From File\n");
    printf("10. Exit\n");
}


// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Read and discard characters until newline or EOF
}


// Functions for each menu option
// function to display student data
void displayStudentData(const struct student *s) {
    printf("--------Student Data --------\n");

    printf("Student Name: %s\n", s->name);
    printf("Roll Number: %d\n", s->roll_number);
    printf("Scores: \n");
    for (int i = 0; i < s->num_scores; i++) {
        if (s->marks[i] <= 40) {
            printf("\t%.2f\tFailed\n", s->marks[i]);
        } else {
            printf("\t%.2f\tPassed\n", s->marks[i]);
        }
    }
    printf("\n");
}


// Function to display all students
void displayAllStudents(const struct student students[],  int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    // Loop through the dynamic student array and display each student's record
    for(int i = 0; i < count; i++) {
        displayStudentData(&students[i]);
    }
}


// Function to input student data
void inputStudentData(struct student *s) {
    printf("Enter student name: ");
    fgets(s->name, sizeof(s->name), stdin);
    s->name[strcspn(s->name, "\n")] = '\0'; // Remove the newline character

    printf("Enter roll number: ");
    scanf("%d", &s->roll_number);
    clearInputBuffer(); // Clear the input buffer after scanf

    printf("Enter the number of scores (up to %d): ", MAX_SCORES);
    scanf("%d", &s->num_scores);
    clearInputBuffer(); // Clear the input buffer after scanf

    // Enforce the MAX_SCORES limit
    if (s->num_scores > MAX_SCORES) {
        printf("Number of scores exceeds the maximum limit. Setting to %d.\n", MAX_SCORES);
        s->num_scores = MAX_SCORES;
    }

    // Allocate memory for the marks array
    s->marks = (float *)malloc(s->num_scores * sizeof(float));
    if (s->marks == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Get each score up to num_scores
    for (int i = 0; i < s->num_scores; i++) {
        printf("Enter score %d: ", i + 1);
        scanf("%f", &s->marks[i]);
        clearInputBuffer(); // Clear the input buffer after scanf
    }
}


// Function to add new student
void addStudent(struct student **students, int *count, int *capacity) {
    if (*count >= *capacity) {
        // Double the capacity
        *capacity *= 2;
        *students = (struct student *)realloc(*students, *capacity * sizeof(struct student));

        if (*students == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    inputStudentData(&(*students)[*count]); // Input data for the new student
    (*count)++; // Increment the student count
    printf("Student added successfuly.\n");
}


// Function to modify a student
void modifyStudent(struct student students[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    int rollNumber;
    printf("Enter the roll number of the student to modify: ");
    scanf("%d", &rollNumber);
    clearInputBuffer(); // Clear the input buffer after scanf

    for (int i = 0; i < count; i++) {
        if (students[i].roll_number == rollNumber) {
            printf("Modifying student with roll number %d:\n", rollNumber);
            inputStudentData(&students[i]); // Re-enter student data
            printf("Student modified successfully.\n");
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber);
}


// Function to delete a student
void deleteStudent(struct student students[], int *count) {
    if (*count == 0) {
        printf("No students found.\n");
        return;
    }

    int rollNumber;
    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &rollNumber);
    clearInputBuffer(); // Clear the input buffer after scanf

    for (int i = 0; i < *count; i++) {
        if (students[i].roll_number == rollNumber) {
            free(students[i].marks); // Free the marks array

            // Shift the remaining students to the left
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }

            (*count)--; // Decrement the student count
            printf("Student deleted successfully.\n");
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber);
}


// Function to save student records to a file
void saveStudentsToFile(const struct student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write each student record to the file
    for (int i = 0; i < count; i++) {
        fprintf(file, "Name: %s\n", students[i].name);
        fprintf(file, "Roll Number: %d\n", students[i].roll_number);
        fprintf(file, "Average Score: %.2f\n", students[i].average_score);
        fprintf(file, "Scores: ");
        for (int j = 0; j < students[i].num_scores; j++) {
            fprintf(file, "%.2f ", students[i].marks[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Student records successfully saved to %s.\n", filename);
}


// Step 4: Update loadStudentsFromFile function
struct student *loadStudentsFromFile(int *count, int *capacity, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing student records found.\n");
        return NULL;
    }

    *count = 0;
    *capacity = INITIAL_CAPACITY;
    struct student *students = (struct student *)malloc(*capacity * sizeof(struct student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return NULL;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Name: ") == line) {
            strcpy(students[*count].name, line + 6);
            students[*count].name[strcspn(students[*count].name, "\n")] = '\0';
        } else if (strstr(line, "Roll Number: ") == line) {
            sscanf(line + 13, "%d", &students[*count].roll_number);
        } else if (strstr(line, "Average Score: ") == line) {
            sscanf(line + 15, "%f", &students[*count].average_score);
        } else if (strstr(line, "Scores: ") == line) {
            students[*count].num_scores = 0;
            students[*count].marks = (float *)malloc(MAX_SCORES * sizeof(float));
            if (students[*count].marks == NULL) {
                printf("Memory allocation failed!\n");
                fclose(file);
                return NULL;
            }

            char *token = strtok(line + 8, " ");
            while (token != NULL && students[*count].num_scores < MAX_SCORES) {
                if(sscanf(token, "%f", &students[*count].marks[students[*count].num_scores]) == 1) {
                    students[*count].num_scores++;
                }
                token = strtok(NULL, " ");
            }
            (*count)++;

            if (*count >= *capacity) {
                *capacity *= 2;
                students = (struct student *)realloc(students, *capacity * sizeof(struct student));
                if (students == NULL) {
                    printf("Memory allocation failed!\n");
                    fclose(file);
                    return NULL;
                }
            }
        }
    }

    fclose(file);
    return students;
}


// Function to insert a student into BST
struct BSTNode *insertIntoBST(struct BSTNode* root, struct student s) {
    if (root == NULL) {
        struct BSTNode* newNode = (struct BSTNode *)malloc(sizeof(struct BSTNode));
        if (!newNode) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
        newNode->data = s;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (s.roll_number < root->data.roll_number) {
        root->left = insertIntoBST(root->left, s);
    } else if (s.roll_number > root->data.roll_number) {
        root->right = insertIntoBST(root->right, s);
    }

    return root;
}


// Function to search for a student in BST
struct student* searchBST(struct BSTNode* root, int roll_number) {
    if (root == NULL || root->data.roll_number == roll_number) {
        return root ? &root->data : NULL;
    }

    if (roll_number < root->data.roll_number) {
        return searchBST(root->left, roll_number);
    } else {
        return searchBST(root->right, roll_number);
    }
}

// Function to free memory allocated for BST
void freeBST(struct BSTNode* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}



// Function to display average score of a student
void displayAverageScore(const struct student students[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n------ Student Average Scores ------\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].roll_number);
        printf("Average Score: %.2f\n", students[i].average_score);
        printf("--------------------------------\n");
    }
}


// Partition function for Quick Sort
int partition(struct student students[], int low, int high, int ascending) {
    float pivot = students[high].average_score;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if ((ascending && students[j].average_score < pivot) || (!ascending && students[j].average_score > pivot)) {
            i++;
            struct student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }

    struct student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;
    return i + 1;
}

// Quick Sort function for sorting students by average score
void quickSort(struct student students[], int low, int high, int ascending) {
    if (low < high) {
        int pi = partition(students, low, high, ascending);
        quickSort(students, low, pi - 1, ascending);
        quickSort(students, pi + 1, high, ascending);
    }
}