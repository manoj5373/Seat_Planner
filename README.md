# CP-036 SeatPlanner: Constraint-Based Exam Seating Allocation System

## Team
Manoj L (1AT24EC079), Prabhath C S (1AT24EC109), C track

## How to run

1. Make sure GCC is installed on your system.
2. Keep `seat_planner.c` and `Student_Database.csv` in the same folder.
3. Open the project folder in the terminal.
4. Compile the program:

```bash
gcc seat_planner.c -o seat_planner.exe
```

5. Run the application:

**Windows PowerShell:**
```powershell
.\seat_planner.exe
```

**MSYS2 / GCC terminal:**
```bash
./seat_planner.exe
```

## Features that work

### Core Features

1. **Room Configuration:** Accepts the number of examination rooms and the number of rows and columns in each room.
2. **Student Data Import:** Reads student information from a CSV file exported from Excel.
3. **Branch-wise Student Management:** Identifies different branches and counts the number of students in each branch.
4. **Seat Allocation:** Automatically allocates students to examination seats.
5. **Branch Adjacency Constraint:** Prevents students belonging to the same branch from occupying adjacent seats.
6. **Room-wise Seating Display:** Displays the seating arrangement with room numbers, rows, benches, register numbers and branch names.
7. **Student Search:** Searches for a student using their register number and displays their name, branch, examination session and seat location.
8. **Menu-driven Interface:** Provides options to view room configuration, branch details, student details, seating arrangement, search students and exit the application.

### Additional Features

1. **Capacity Checking:** Checks whether the available seating capacity is sufficient for all students.
2. **Additional Room Requirement:** Calculates the additional benches and seats required when the existing arrangement is insufficient.
3. **Two-session Arrangement:** Divides complete branches between morning and afternoon examination sessions when additional rooms are unavailable.
4. **Duplicate Register Number Detection:** Detects duplicate register numbers in the CSV file and reports the duplicate record.
5. **CSV Validation:** Detects incomplete student records and skips invalid rows.
6. **Dynamic Branch Detection:** Identifies branches automatically from the CSV file without requiring branch names to be hardcoded.

## Sample run

```text
===================================
        EXAM SEAT PLANNER
===================================

Enter number of rooms: 1

Room 1
Enter rows: 3
Enter columns: 4

Total seating capacity: 24

Student data imported successfully from CSV!

ECE: 8 students
CSE: 8 students
ISE: 8 students

Total students: 24

=======================================
             SEATPLANNER MENU
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit

Enter your choice: 2

========== BRANCH DETAILS ==========

ECE: 8
CSE: 8
ISE: 8

Total number of students: 24

Enter your choice: 6

Thank you for using SeatPlanner!
```

