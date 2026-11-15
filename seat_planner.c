
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 10
#define MAX_ROWS 20
#define MAX_COLS 20
#define MAX_BRANCHES 10
#define MAX_STUDENTS 500

struct Seat {
    char regNo[20];
    char studentName[50];
    int branch;
    int occupied;
};

struct Seat seats[2][MAX_ROOMS][MAX_ROWS][MAX_COLS][2];

char branchName[MAX_BRANCHES][20];
char students[MAX_BRANCHES][MAX_STUDENTS][20];
char studentNames[MAX_BRANCHES][MAX_STUDENTS][50];

int studentCount[MAX_BRANCHES];
int rows[MAX_ROOMS], cols[MAX_ROOMS];
int rooms, branches, capacity = 0;
int totalStudents = 0;
int sessions = 1;
int branchSession[MAX_BRANCHES];

// Calculate capacity of one room
int roomCapacity(int r)
{
    return rows[r] * cols[r] * 2;
}

// Maximum number of students from ONE branch that can be seated
// without sitting next to another student of the same branch.
// Each row has 2 * columns seats, so at most columns positions
// can be occupied by one branch in that row.
int branchSlotCapacity()
{
    int r;
    int slots = 0;

    for (r = 0; r < rooms; r++)
        slots += rows[r] * cols[r];

    return slots;
}

int largestBranchCount()
{
    int b;
    int largest = 0;

    for (b = 0; b < branches; b++)
    {
        if (studentCount[b] > largest)
            largest = studentCount[b];
    }

    return largest;
}

// Add examination rooms
void addRooms()
{
    int n, i;

    printf("\nHow many rooms do you want to add? ");
    scanf("%d", &n);

    if (n <= 0 || rooms + n > MAX_ROOMS)
    {
        printf("Invalid number of rooms!\n");
        return;
    }

    for (i = rooms; i < rooms + n; i++)
    {
        printf("\nRoom %d\n", i + 1);

        printf("Enter rows: ");
        scanf("%d", &rows[i]);

        printf("Enter columns: ");
        scanf("%d", &cols[i]);

        if (rows[i] < 1 || rows[i] > MAX_ROWS ||
            cols[i] < 1 || cols[i] > MAX_COLS)
        {
            printf("Invalid room dimensions!\n");
            return;
        }

        capacity += roomCapacity(i);
        printf("Room capacity: %d\n", roomCapacity(i));
    }

    rooms += n;
    printf("\nUpdated total capacity: %d\n", capacity);
}

// Read student details from the CSV file exported from Excel.
// Expected columns: Branch,Register Number,Student Name
void inputStudents()
{
    FILE *fp;
    char line[256];
    char *branch, *regNo, *studentName;
    int b, existingBranch, existingStudent;
    int csvRow = 1;

    fp = fopen("Student_Database.csv", "r");
    if (fp == NULL)
    {
        printf("\nERROR: Could not open Student_Database.csv\n");
        printf("Keep the CSV file in the same folder as Seat_planner.exe.\n");
        exit(1);
    }

    // Skip the header row.
    if (fgets(line, sizeof(line), fp) == NULL)
    {
        printf("\nERROR: The CSV file is empty.\n");
        fclose(fp);
        exit(1);
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        csvRow++;
        // Remove newline characters.
        line[strcspn(line, "\r\n")] = '\0';

        branch = strtok(line, ",");
        regNo = strtok(NULL, ",");
        studentName = strtok(NULL, ",");

        if (branch == NULL || regNo == NULL || studentName == NULL)
        {
            printf("\nWARNING: Skipping an incomplete CSV row.\n");
            continue;
        }

        // Remove leading spaces from fields.
        while (*branch == ' ' || *branch == '\t') branch++;
        while (*regNo == ' ' || *regNo == '\t') regNo++;
        while (*studentName == ' ' || *studentName == '\t') studentName++;

        // Remove trailing spaces and tabs from all fields.
        branch[strcspn(branch, " \t")] = '\0';
        {
            size_t len = strlen(regNo);
            while (len > 0 && (regNo[len - 1] == ' ' || regNo[len - 1] == '\t'))
                regNo[--len] = '\0';
        }
        {
            size_t len = strlen(studentName);
            while (len > 0 && (studentName[len - 1] == ' ' || studentName[len - 1] == '\t'))
                studentName[--len] = '\0';
        }

        if (regNo[0] == '\0' || branch[0] == '\0' || studentName[0] == '\0')
        {
            printf("\nWARNING: Skipping an incomplete CSV row (row %d).\n", csvRow);
            continue;
        }

        // Register numbers must be unique across the entire database,
        // including students belonging to different branches.
        for (existingBranch = 0; existingBranch < branches; existingBranch++)
        {
            for (existingStudent = 0;
                 existingStudent < studentCount[existingBranch];
                 existingStudent++)
            {
                if (strcmp(students[existingBranch][existingStudent], regNo) == 0)
                {
                    printf("\nERROR: Duplicate register number detected!\n");
                    printf("Register Number: %s\n", regNo);
                    printf("First record:  %s (%s)\n",
                           studentNames[existingBranch][existingStudent],
                           branchName[existingBranch]);
                    printf("Duplicate row: %d - %s (%s)\n",
                           csvRow, studentName, branch);
                    printf("Please correct the duplicate in Student_Database.csv and run again.\n");
                    fclose(fp);
                    exit(1);
                }
            }
        }

        // Find an existing branch or create a new one.
        for (b = 0; b < branches; b++)
        {
            if (strcmp(branchName[b], branch) == 0)
                break;
        }

        if (b == branches)
        {
            if (branches >= MAX_BRANCHES)
            {
                printf("\nERROR: Maximum number of branches exceeded.\n");
                fclose(fp);
                exit(1);
            }
            strcpy(branchName[branches], branch);
            branches++;
        }

        if (studentCount[b] >= MAX_STUDENTS)
        {
            printf("\nERROR: Maximum student count exceeded for %s.\n", branch);
            fclose(fp);
            exit(1);
        }

        strcpy(students[b][studentCount[b]], regNo);
        strcpy(studentNames[b][studentCount[b]], studentName);
        studentCount[b]++;
        totalStudents++;
    }

    fclose(fp);

    if (totalStudents == 0)
    {
        printf("\nERROR: No student records were found in the CSV file.\n");
        exit(1);
    }

    printf("\nStudent data imported successfully from CSV!\n");
    for (b = 0; b < branches; b++)
    {
        printf("  %s: %d students\n", branchName[b], studentCount[b]);
    }
    printf("  Total students: %d\n", totalStudents);
}

// Divide complete branches between two sessions
int divideSessions()
{
    int mask, i;
    int bestMask = -1;
    int bestDifference = totalStudents + 1;
    int maxBranchSlots = branchSlotCapacity();

    // A branch cannot have more students than the number of
    // non-adjacent positions available across all rows.
    for (i = 0; i < branches; i++)
    {
        if (studentCount[i] > maxBranchSlots)
            return 0;
    }

    // Try all possible groups of branches
    for (mask = 1; mask < (1 << branches) - 1; mask++)
    {
        int morning = 0;
        int afternoon;
        int difference;

        for (i = 0; i < branches; i++)
        {
            if (mask & (1 << i))
                morning += studentCount[i];
        }

        afternoon = totalStudents - morning;

        if (morning <= capacity && afternoon <= capacity)
        {
            difference = abs(morning - afternoon);

            if (difference < bestDifference)
            {
                bestDifference = difference;
                bestMask = mask;
            }
        }
    }

    if (bestMask == -1)
        return 0;

    for (i = 0; i < branches; i++)
    {
        if (bestMask & (1 << i))
            branchSession[i] = 0;
        else
            branchSession[i] = 1;
    }

    sessions = 2;
    return 1;
}

// Allocate seats for one session.
// Students are placed in left-to-right order across each row.
// The next student must be from a different branch than the
// immediately previous occupied seat. We do not reserve a whole
// room for one branch, because that can leave alternate seats empty.
int allocateSeats(int session)
{
    int nextStudent[MAX_BRANCHES] = {0};
    int i, j, k, s;
    int allocated = 0;
    int required = 0;
    int allocatedByBranch[MAX_BRANCHES] = {0};

    for (i = 0; i < branches; i++)
    {
        if (branchSession[i] == session)
            required += studentCount[i];
    }

    // Clear all seats for this session before allocation.
    for (i = 0; i < rooms; i++)
    {
        for (j = 0; j < rows[i]; j++)
        {
            for (k = 0; k < cols[i] * 2; k++)
            {
                int bench = k / 2;
                int seatNo = k % 2;
                seats[session][i][j][bench][seatNo].occupied = 0;
                seats[session][i][j][bench][seatNo].branch = -1;
            }
        }
    }

    for (i = 0; i < rooms; i++)
    {
        for (j = 0; j < rows[i]; j++)
        {
            int previousBranch = -1;

            // A row is treated as one continuous line of seats:
            // seat 1 and seat 2 of a bench, then the next bench.
            for (k = 0; k < cols[i] * 2; k++)
            {
                int selected = -1;
                int maximum = -1;
                int bench = k / 2;
                int seatNo = k % 2;

                // Choose the eligible branch with the most students left.
                // Never put the same branch in consecutive seats.
                for (s = 0; s < branches; s++)
                {
                    int remaining = studentCount[s] - nextStudent[s];

                    if (branchSession[s] == session &&
                        remaining > 0 &&
                        s != previousBranch && remaining > maximum)
                    {
                        maximum = remaining;
                        selected = s;
                    }
                }

                if (selected == -1)
                {
                    // If only the previous branch has students remaining,
                    // leave this seat empty as a separator. The next seat
                    // can then be used without placing same-branch students
                    // in adjacent seats.
                    previousBranch = -1;
                    continue;
                }

                strcpy(seats[session][i][j][bench][seatNo].regNo,
                       students[selected][nextStudent[selected]]);
                strcpy(seats[session][i][j][bench][seatNo].studentName,
                       studentNames[selected][nextStudent[selected]]);

                seats[session][i][j][bench][seatNo].branch = selected;
                seats[session][i][j][bench][seatNo].occupied = 1;

                nextStudent[selected]++;
                allocatedByBranch[selected]++;
                allocated++;
                previousBranch = selected;
            }
        }
    }

    printf("\nSession %d: Allocated %d out of %d students\n",
           session + 1, allocated, required);

    for (s = 0; s < branches; s++)
    {
        if (branchSession[s] == session)
        {
            printf("  %s: %d / %d allocated\n",
                   branchName[s], allocatedByBranch[s], studentCount[s]);
        }
    }

    if (allocated < required)
    {
        printf("WARNING: %d students could not be seated.\n",
               required - allocated);
        printf("The branch counts and row-wise adjacency constraint "
               "need a different arrangement or more capacity.\n");
    }

    return allocated;
}

// Print the seating arrangement with fixed-width columns.
// Only register number and branch are displayed; student names remain available for search.
void displaySeats(int session)
{
    int i, j, k, s;

    if (session == 0)
        printf("\n===== MORNING: 8 AM - 10 AM =====\n");
    else
        printf("\n===== AFTERNOON: 2 PM - 4 PM =====\n");

    for (i = 0; i < rooms; i++)
    {
        printf("\nROOM %d\n", i + 1);

        for (j = 0; j < rows[i]; j++)
        {
            printf("\nRow %d:\n", j + 1);

            for (k = 0; k < cols[i]; k++)
            {
                printf("Bench %-2d: ", k + 1);

                for (s = 0; s < 2; s++)
                {
                    struct Seat *p = &seats[session][i][j][k][s];

                    if (p->occupied)
                    {
                        // Display only register number and branch.
                        // Fixed widths keep every seat column aligned.
                        printf("[%-19.19s | %-8.8s] ",
                               p->regNo,
                               branchName[p->branch]);
                    }
                    else
                    {
                        printf("[%-19s | %-8s] ", "EMPTY", "");
                    }
                }

                printf("\n");
            }
        }
    }
}


// Display the configured examination rooms.
void showRoomConfiguration()
{
    int i;

    printf("\n========== ROOM CONFIGURATION ==========\n");
    for (i = 0; i < rooms; i++)
    {
        printf("Room %d: %d rows x %d benches\n",
               i + 1, rows[i], cols[i]);
        printf("Capacity: %d students\n", roomCapacity(i));
    }
    printf("---------------------------------------\n");
    printf("Total rooms: %d\n", rooms);
    printf("Total seating capacity: %d\n", capacity);
    printf("Total students: %d\n", totalStudents);
}

// Display all student records imported from the CSV file.
void showStudentDetails()
{
    int b, j;

    printf("\n========== STUDENT DETAILS ==========\n");
    for (b = 0; b < branches; b++)
    {
        printf("\nBranch: %s (%d students)\n",
               branchName[b], studentCount[b]);
        printf("%-20s %-25s\n", "Register Number", "Student Name");
        printf("-----------------------------------------------\n");

        for (j = 0; j < studentCount[b]; j++)
        {
            printf("%-20s %-25s\n",
                   students[b][j], studentNames[b][j]);
        }
    }
    printf("\nTotal students: %d\n", totalStudents);
}

// Display branch-wise student counts without listing individual students.
void showBranchDetails()
{
    int b;

    printf("\n========== BRANCH DETAILS ==========\n");
    printf("%-20s %s\n", "Branch", "Number of Students");
    printf("------------------------------------\n");

    for (b = 0; b < branches; b++)
    {
        printf("%-20s %d\n", branchName[b], studentCount[b]);
    }

    printf("------------------------------------\n");
    printf("Total number of students: %d\n", totalStudents);
}

// Search for every student record matching a register number.
// This is useful when test data contains the same number in different branches.
void searchStudent()
{
    char regNo[20];
    int t, i, j, k, s;
    int matches = 0;

    printf("\nEnter register number to search: ");
    scanf("%19s", regNo);

    for (t = 0; t < sessions; t++)
    {
        for (i = 0; i < rooms; i++)
        {
            for (j = 0; j < rows[i]; j++)
            {
                for (k = 0; k < cols[i]; k++)
                {
                    for (s = 0; s < 2; s++)
                    {
                        struct Seat *p = &seats[t][i][j][k][s];

                        if (p->occupied && strcmp(p->regNo, regNo) == 0)
                        {
                            matches++;
                            printf("\nMatch %d found!\n", matches);
                            printf("Register No: %s\n", p->regNo);
                            printf("Name: %s\n", p->studentName);
                            printf("Branch: %s\n", branchName[p->branch]);

                            if (sessions == 2)
                            {
                                if (t == 0)
                                    printf("Session: Morning (8 AM - 10 AM)\n");
                                else
                                    printf("Session: Afternoon (2 PM - 4 PM)\n");
                            }
                            else
                            {
                                printf("Session: Single Session\n");
                            }

                            printf("Room: %d\n", i + 1);
                            printf("Row: %d\n", j + 1);
                            printf("Bench: %d\n", k + 1);
                            printf("Seat: %d\n", s + 1);
                        }
                    }
                }
            }
        }
    }

    if (matches == 0)
        printf("\nStudent not found in seating arrangement.\n");
    else if (matches > 1)
        printf("\nNote: %d matching records were found. Check the branch and register number.\n",
               matches);
}

int main()
{
    int i, t;
    int totalAllocated = 0;
    int menuChoice = 0;
    char choice;

    printf("===================================\n");
    printf("        EXAM SEAT PLANNER\n");
    printf("===================================\n");

    printf("\nEnter number of rooms: ");
    scanf("%d", &rooms);

    if (rooms < 1 || rooms > MAX_ROOMS)
    {
        printf("Invalid number of rooms!\n");
        return 1;
    }

    for (i = 0; i < rooms; i++)
    {
        printf("\nRoom %d\n", i + 1);

        printf("Enter rows: ");
        scanf("%d", &rows[i]);

        printf("Enter columns: ");
        scanf("%d", &cols[i]);

        if (rows[i] < 1 || rows[i] > MAX_ROWS ||
            cols[i] < 1 || cols[i] > MAX_COLS)
        {
            printf("Invalid room dimensions!\n");
            return 1;
        }

        capacity += roomCapacity(i);
    }

    printf("\nTotal seating capacity: %d\n", capacity);

    inputStudents();

    printf("\nTotal students appearing: %d\n", totalStudents);

    // Check seating capacity
    while (totalStudents > capacity ||
           largestBranchCount() > branchSlotCapacity())
    {
        printf("\nINSUFFICIENT SEATING ARRANGEMENT!\n");
        printf("\nNOTE: An additional room is required for a single-session ");
        printf("exam when the available seats or non-adjacent bench positions ");
        printf("are insufficient.\n");

        printf("\nCurrent details:\n");
        printf("  Total students: %d\n", totalStudents);
        printf("  Available seats: %d\n", capacity);
        printf("  Available benches (one non-adjacent position per bench): %d\n",
               branchSlotCapacity());
        printf("  Largest branch: %d students\n", largestBranchCount());

        {
            int seatShortage = totalStudents - capacity;
            int benchShortage = largestBranchCount() - branchSlotCapacity();
            int benchesToAdd = 0;

            if (seatShortage < 0)
                seatShortage = 0;
            if (benchShortage < 0)
                benchShortage = 0;

            // Each bench provides two seats, and one non-adjacent
            // position for students from any one branch.
            benchesToAdd = (seatShortage + 1) / 2;
            if (benchShortage > benchesToAdd)
                benchesToAdd = benchShortage;

            if (benchesToAdd > 0)
            {
                printf("\nNOTE - Additional room requirement:\n");
                printf("  Minimum additional benches needed: %d\n", benchesToAdd);
                printf("  Minimum additional seats needed: %d\n", benchesToAdd * 2);
                if (seatShortage > 0)
                    printf("  Reason 1: Overall seat shortage = %d seats.\n",
                           seatShortage);
                if (benchShortage > 0)
                    printf("  Reason 2: The largest branch needs %d more non-adjacent bench positions.\n",
                           benchShortage);
                printf("  Add room(s) whose combined capacity provides at least this requirement.\n");
            }
        }

        printf("\nYou may add rooms for a single-session arrangement, or enter N ");
        printf("to try dividing complete branches into two sessions.\n");
        printf("Can you arrange additional rooms? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y')
        {
            addRooms();
        }
        else if (choice == 'N' || choice == 'n')
        {
            printf("\nTrying two examination sessions...\n");

            if (!divideSessions())
            {
                printf("\nCannot create a valid two-session arrangement.\n");
                printf("At least one branch has more students than the available non-adjacent seat positions, or no branch grouping fits both sessions.\n");
                printf("Add rooms/seats, or change the rule that keeps each branch in one session.\n");
                return 1;
            }

            break;
        }
        else
        {
            printf("Please enter Y or N.\n");
        }
    }

    // Single session if all students fit
    if (sessions == 1)
    {
        for (i = 0; i < branches; i++)
            branchSession[i] = 0;
    }

    // Print session branch details
    for (t = 0; t < sessions; t++)
    {
        int count = 0;

        if (sessions == 2)
        {
            if (t == 0)
                printf("\nMORNING SESSION: 8 AM - 10 AM\n");
            else
                printf("\nAFTERNOON SESSION: 2 PM - 4 PM\n");
        }
        else
        {
            printf("\nSINGLE EXAM SESSION\n");
        }

        printf("Branches: ");

        for (i = 0; i < branches; i++)
        {
            if (branchSession[i] == t)
            {
                printf("%s ", branchName[i]);
                count += studentCount[i];
            }
        }

        printf("\nStudents: %d\n", count);
    }

    // Allocate seats once. The menu can display the saved arrangement
    // whenever the user selects option 3.
    for (t = 0; t < sessions; t++)
        totalAllocated += allocateSeats(t);

    printf("\nTOTAL ALLOCATED: %d / %d\n",
           totalAllocated, totalStudents);

    if (totalAllocated != totalStudents)
    {
        printf("Allocation incomplete. Review seating "
               "before finalizing the exam plan.\n");
    }

    // Main menu
    do
    {
        printf("\n=======================================\n");
        printf("             SEATPLANNER MENU           \n");
        printf("=======================================\n");
        printf("1. Show Room Configuration\n");
        printf("2. Show Branch Details\n");
        printf("3. Show Student Details\n");
        printf("4. Display Seating Arrangement\n");
        printf("5. Search Student by Register Number\n");
        printf("6. Exit\n");
        printf("---------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &menuChoice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (menuChoice)
        {
            case 1:
                showRoomConfiguration();
                break;

            case 2:
                showBranchDetails();
                break;

            case 3:
                showStudentDetails();
                break;

            case 4:
                for (t = 0; t < sessions; t++)
                    displaySeats(t);
                break;

            case 5:
                searchStudent();
                break;

            case 6:
                printf("\nThank you for using SeatPlanner!\n");
                break;

            default:
                printf("\nInvalid choice. Please select 1 to 6.\n");
        }

    } while (menuChoice != 6);

    return 0;
}
