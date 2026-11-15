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

Enter number of rooms: 2

Room 1
Enter rows: 5
Enter columns: 3

Room 2
Enter rows: 5
Enter columns: 3

Total seating capacity: 60

Student data imported successfully from CSV!
  ECE: 20 students
  CSE: 20 students
  ISE: 20 students
  Total students: 60

Total students appearing: 60

SINGLE EXAM SESSION
Branches: ECE CSE ISE 
Students: 60

Session 1: Allocated 60 out of 60 students
  ECE: 20 / 20 allocated
  CSE: 20 / 20 allocated
  ISE: 20 / 20 allocated

TOTAL ALLOCATED: 60 / 60

=======================================
             SEATPLANNER MENU           
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit
---------------------------------------
Enter your choice: 1

========== ROOM CONFIGURATION ==========
Room 1: 5 rows x 3 benches
Capacity: 30 students
Room 2: 5 rows x 3 benches
Capacity: 30 students
---------------------------------------
Total rooms: 2
Total seating capacity: 60
Total students: 60

=======================================
             SEATPLANNER MENU           
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit
---------------------------------------
Enter your choice: 2

========== BRANCH DETAILS ==========
Branch               Number of Students
------------------------------------
ECE                  20
CSE                  20
ISE                  20
------------------------------------
Total number of students: 60

=======================================
             SEATPLANNER MENU           
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit
---------------------------------------
Enter your choice: 3

========== STUDENT DETAILS ==========

Branch: ECE (20 students)
Register Number      Student Name             
-----------------------------------------------
1AT24EC001           student-1                
1AT24EC002           student-2                
1AT24EC003           student-3                
1AT24EC004           student-4                
1AT24EC005           student-5                
1AT24EC006           student-6                
1AT24EC007           student-7                
1AT24EC008           student-8                
1AT24EC009           student-9                
1AT24EC010           student-10               
1AT24EC011           student-11               
1AT24EC012           student-12               
1AT24EC013           student-13               
1AT24EC014           student-14               
1AT24EC015           student-15               
1AT24EC016           student-16               
1AT24EC017           student-17               
1AT24EC018           student-18               
1AT24EC019           student-19               
1AT24EC020           student-20               

Branch: CSE (20 students)
Register Number      Student Name             
-----------------------------------------------
1AT24CS001           student-1                
1AT24CS002           student-2                
1AT24CS003           student-3                
1AT24CS004           student-4                
1AT24CS005           student-5                
1AT24CS006           student-6                
1AT24CS007           student-7                
1AT24CS008           student-8                
1AT24CS009           student-9                
1AT24CS010           student-10               
1AT24CS011           student-11               
1AT24CS012           student-12               
1AT24CS013           student-13               
1AT24CS014           student-14               
1AT24CS015           student-15               
1AT24CS016           student-16               
1AT24CS017           student-17               
1AT24CS018           student-18               
1AT24CS019           student-19               
1AT24CS020           student-20               

Branch: ISE (20 students)
Register Number      Student Name             
-----------------------------------------------
1AT24IS001           student-1                
1AT24IS002           student-2                
1AT24IS003           student-3                
1AT24IS004           student-4                
1AT24IS005           student-5                
1AT24IS006           student-6                
1AT24IS007           student-7                
1AT24IS008           student-8                
1AT24IS009           student-9                
1AT24IS010           student-10               
1AT24IS011           student-11               
1AT24IS012           student-12               
1AT24IS013           student-13               
1AT24IS014           student-14               
1AT24IS015           student-15               
1AT24IS016           student-16               
1AT24IS017           student-17               
1AT24IS018           student-18               
1AT24IS019           student-19               
1AT24IS020           student-20               

Total students: 60

=======================================
             SEATPLANNER MENU           
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit
---------------------------------------
Enter your choice: 4

===== MORNING: 8 AM - 10 AM =====

ROOM 1

Row 1:
Bench 1 : [1AT24EC001          | ECE     ] [1AT24CS001          | CSE     ] 
Bench 2 : [1AT24IS001          | ISE     ] [1AT24EC002          | ECE     ] 
Bench 3 : [1AT24CS002          | CSE     ] [1AT24IS002          | ISE     ] 

Row 2:
Bench 1 : [1AT24EC003          | ECE     ] [1AT24CS003          | CSE     ] 
Bench 2 : [1AT24IS003          | ISE     ] [1AT24EC004          | ECE     ] 
Bench 3 : [1AT24CS004          | CSE     ] [1AT24IS004          | ISE     ] 

Row 3:
Bench 1 : [1AT24EC005          | ECE     ] [1AT24CS005          | CSE     ] 
Bench 2 : [1AT24IS005          | ISE     ] [1AT24EC006          | ECE     ] 
Bench 3 : [1AT24CS006          | CSE     ] [1AT24IS006          | ISE     ] 

Row 4:
Bench 1 : [1AT24EC007          | ECE     ] [1AT24CS007          | CSE     ] 
Bench 2 : [1AT24IS007          | ISE     ] [1AT24EC008          | ECE     ] 
Bench 3 : [1AT24CS008          | CSE     ] [1AT24IS008          | ISE     ] 

Row 5:
Bench 1 : [1AT24EC009          | ECE     ] [1AT24CS009          | CSE     ] 
Bench 2 : [1AT24IS009          | ISE     ] [1AT24EC010          | ECE     ] 
Bench 3 : [1AT24CS010          | CSE     ] [1AT24IS010          | ISE     ] 

ROOM 2

Row 1:
Bench 1 : [1AT24EC011          | ECE     ] [1AT24CS011          | CSE     ] 
Bench 2 : [1AT24IS011          | ISE     ] [1AT24EC012          | ECE     ] 
Bench 3 : [1AT24CS012          | CSE     ] [1AT24IS012          | ISE     ] 

Row 2:
Bench 1 : [1AT24EC013          | ECE     ] [1AT24CS013          | CSE     ] 
Bench 2 : [1AT24IS013          | ISE     ] [1AT24EC014          | ECE     ] 
Bench 3 : [1AT24CS014          | CSE     ] [1AT24IS014          | ISE     ] 

Row 3:
Bench 1 : [1AT24EC015          | ECE     ] [1AT24CS015          | CSE     ] 
Bench 2 : [1AT24IS015          | ISE     ] [1AT24EC016          | ECE     ] 
Bench 3 : [1AT24CS016          | CSE     ] [1AT24IS016          | ISE     ] 

Row 4:
Bench 1 : [1AT24EC017          | ECE     ] [1AT24CS017          | CSE     ] 
Bench 2 : [1AT24IS017          | ISE     ] [1AT24EC018          | ECE     ] 
Bench 3 : [1AT24CS018          | CSE     ] [1AT24IS018          | ISE     ] 

Row 5:
Bench 1 : [1AT24EC019          | ECE     ] [1AT24CS019          | CSE     ] 
Bench 2 : [1AT24IS019          | ISE     ] [1AT24EC020          | ECE     ] 
Bench 3 : [1AT24CS020          | CSE     ] [1AT24IS020          | ISE     ] 

=======================================
             SEATPLANNER MENU           
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit
---------------------------------------
Enter your choice: 5

Enter register number to search: 1AT24EC018

Match 1 found!
Register No: 1AT24EC018
Name: student-18
Branch: ECE
Session: Single Session
Room: 2
Row: 4
Bench: 2
Seat: 2

=======================================
             SEATPLANNER MENU           
=======================================
1. Show Room Configuration
2. Show Branch Details
3. Show Student Details
4. Display Seating Arrangement
5. Search Student by Register Number
6. Exit
---------------------------------------
Enter your choice: 6

Thank you for using SeatPlanner!

Enter your choice: 6

Thank you for using SeatPlanner!
```

