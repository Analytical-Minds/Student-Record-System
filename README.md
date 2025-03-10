# Student Score Record System

## 📌 Overview
The **Student Score Record System** is a C-based program that allows users to **store, manage, and analyze student records** efficiently.  
It features **CRUD operations**, **searching by roll number (via Binary Search Tree)**, and **sorting by average score (via Quick Sort)**.  
Data persistence is ensured by saving and loading student records to/from a file.

---

## 🚀 Features
✔️ **Add Student Records** - Enter student name, roll number, and scores.  
✔️ **Modify Student Records** - Update a student's details.  
✔️ **Delete Student Records** - Remove a student from the database.  
✔️ **Search for a Student** - Find a student **by roll number** using a **Binary Search Tree (BST)**.  
✔️ **Calculate Average Scores** - Compute and store the average score for each student.  
✔️ **Sort Students by Average Score** - Use **Quick Sort** to sort in **ascending or descending order**.  
✔️ **Save and Load Records from File** - Ensures persistence between program runs.  

---

## 📜 How It Works

### ✅ **Data Structure Choices**
- **Binary Search Tree (BST)** is used for **efficient searching** by roll number.  
- **Dynamic Array** is used to store student records in memory.  
- **Quick Sort** is used for sorting students **by their average score**.  

### ✅ **File Handling**
- Data is stored in `students.txt` in the following format:
    ```
    Name: John Doe
    Roll Number: 12
    Average Score: 85.67
    Scores: 78.50 90.00 88.50
    ```
- Records are **saved** when the user selects **"Save to File"**.  
- When **loading from a file**, data is dynamically allocated and added to both the array and BST.

---

## 🛠️ Installation and Usage

### **1️⃣ Compile the Program**
Use **GCC** or any compatible C compiler:
```bash
gcc main.c functions.c -o student_records
```

### **2️⃣ Run the Program**
```bash
./student_records
```

### **3️⃣ Follow the On-Screen Menu**
```
----------- Menu -----------
1. Display Student Records
2. Add Student Record
3. Modify Student Record
4. Delete Student Record
5. Search for a Student
6. Calculate Average Score
7. Sort Student Records by Average Score
8. Save Records to File
9. Load Records from File
10. Exit
```

---

## 📂 Project Structure
```
📁 Student-Record-System
│── main.c             # Contains the main program logic
│── functions.c        # Implements all function definitions
│── main.h             # Header file with function prototypes & struct definitions
│── students.txt       # Stores student records
│── README.md          # Project documentation
```

---

## 🔧 Functions Breakdown

### 📌 **Core Functions**
| Function Name            | Description |
|--------------------------|-------------|
| `addStudent()`           | Adds a new student to the array. |
| `modifyStudent()`        | Modifies an existing student’s data. |
| `deleteStudent()`        | Removes a student record. |
| `searchBST()`            | Searches for a student **by roll number** using BST. |
| `quickSort()`            | Sorts students **by average score**. |
| `saveStudentsToFile()`   | Saves student records to `students.txt`. |
| `loadStudentsFromFile()` | Loads student records from `students.txt`. |

---

## 🏆 Example Usage
### **Adding a Student**
```
Enter student name: Alice Johnson
Enter roll number: 5
Enter number of scores: 3
Enter score 1: 78.5
Enter score 2: 90
Enter score 3: 88
Student added successfully.
```

### **Sorting Students by Average Score**
```
Choose sorting order:
1. Ascending
2. Descending
Enter choice: 1

Students sorted by average score:
--------------------------------
Name: Alice Johnson
Roll Number: 5
Average Score: 85.50
--------------------------------
```

### **Searching for a Student by Roll Number**
```
Enter roll number to search: 5
Student found:
---------------------------
Name: Alice Johnson
Roll Number: 5
Average Score: 85.50
---------------------------
```

---

## 💡 Future Improvements
- ✅ Implement a **graphical user interface (GUI)**.  
- ✅ Add **support for exporting records in CSV format**.  
- ✅ Implement a **database backend (SQLite/PostgreSQL)** for large-scale storage.  

---

## 🏷️ License
This project is **open-source** and available under the **MIT License**.

---

## 📞 Contact
For questions, contributions, or issues, contact:  
📧 **your-email@example.com**  
🔗 **GitHub: [YourGitHubUsername](https://github.com/YourGitHubUsername)**
