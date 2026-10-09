# I/O Functions Documentation for Gym Management System

## Overview
I've added I/O (Input/Output) functions to every class in the gym management system to enable:
1. **Saving records to files** - Persist data across program runs
2. **Loading records from files** - Retrieve saved data
3. **Formatted display** - Display records in clean, organized format

---

## I/O Functions Added to Each Class

### 1. **Person Class** (person.cpp / Person.h)
- **`void saveToFile(const string& filename) const`**
  - Appends person record to file in format: `ID|FirstName|LastName|ContactInfo`
  - Example: `1|John|Doe|555-1234`

- **`static void loadFromFile(const string& filename)`**
  - Reads and displays all person records from file
  - Shows formatted header and footer

- **`void displayFormatted() const`**
  - Displays person information in clean table format with separators

---

### 2. **Member Class** (Member.cpp / Member.h)
- **`void saveToFile(const string& filename) const`**
  - Saves: `ID|Name|Age|Gender|Contact|Plan|RegDate|ExpDate|Trainer|Status`
  - Example: `101|Jane Smith|25|Female|555-5678|Premium|2024-01-15|2024-12-15|John Trainer|Active`

- **`static void loadFromFile(const string& filename)`**
  - Displays all member records from file with formatted output

- **`void displayFormatted() const`**
  - Shows member details in aligned table format with borders

---

### 3. **Trainer Class** (Trainer.cpp / Trainer.h)
- **`void saveToFile(const string& filename) const`**
  - Saves: `ID|Name|Contact|Specialty|Salary|MembersAssigned`
  - Example: `2|John Trainer|555-9999|CrossFit|50000|5`

- **`static void loadFromFile(const string& filename)`**
  - Displays all trainer records with formatting

- **`void displayFormatted() const`**
  - Shows trainer details in clean formatted table

---

### 4. **Exercise Class** (Exercise.cpp / Exercise.h)
- **`void saveToFile(const string& filename) const`**
  - Saves: `ExerciseName|Sets|Reps|RestTime`
  - Example: `Bench Press|4|10|90`

- **`static void loadFromFile(const string& filename)`**
  - Displays all exercise records

- **`void displayFormatted() const`**
  - Shows exercise details in formatted output

---

### 5. **WorkoutProgram Class** (workoutprogram.cpp / WorkoutProgram.h)
- **`void saveToFile(const string& filename) const`**
  - Saves: `ProgramID|Name|TargetGoal|Duration|TrainerName|ExerciseCount`
  - Example: `201|Summer Body|Weight Loss|12 weeks|John Trainer|6`

- **`static void loadFromFile(const string& filename)`**
  - Displays all workout program records

- **`void displayFormatted() const`**
  - Shows program details in formatted table

---

### 6. **Payment Class** (Payment.cpp / Payment.h)
- **`void saveToFile(const string& filename) const`**
  - Saves: `PaymentID|MemberID|Amount|Date|Method|Status|Discount|Penalty`
  - Example: `PAY-0001|101|100|2024-05-01|Credit Card|Completed|10|0`

- **`static void loadFromFile(const string& filename)`**
  - Displays all payment records

- **`void displayFormatted() const`**
  - Shows payment details in clean formatted table with currency

---

### 7. **AttendanceRecord Class** (attendance.cpp / AttendanceRecord.h)
- **`void saveToFile(const string& filename) const`**
  - Saves: `MemberID|Date|CheckInTime|CheckOutTime`
  - Example: `101|2024-05-01|09:00|11:30`

- **`static void loadFromFile(const string& filename)`**
  - Displays all attendance records

- **`void displayFormatted() const`**
  - Shows attendance details in formatted table

---

### 8. **GymController Class** (GymController.cpp / GymController.h)
- **`void saveAllDataToFile(const string& filename) const`**
  - Saves all data (members, trainers, payments, attendance) to single file
  - Organizes data by sections: `=== MEMBERS ===`, `=== TRAINERS ===`, etc.
  - Creates complete backup of entire gym database

- **`void loadAllDataFromFile(const string& filename)`**
  - Loads previously saved data from file (ready for enhancement)

- **`void displayFormattedReport() const`**
  - Displays comprehensive formatted report with:
    - Members summary (total, active count)
    - Trainers summary
    - Payments summary (total revenue, completed payments)
    - Attendance summary

---

## Usage Example

```cpp
// Create a member
Member m(1, "John Doe", 30, "Male", "555-1234", "Premium", "2024-01-01", "2024-12-31", "Trainer1");

// Save to file
m.saveToFile("members.txt");

// Display formatted
m.displayFormatted();

// Load all members from file
Member::loadFromFile("members.txt");

// For GymController
GymController gym;
gym.addMember(m);
gym.addTrainer(trainer);
gym.recordPayment(payment);
gym.recordAttendance(attendance);

// Save all data
gym.saveAllDataToFile("gym_backup.txt");

// Display formatted report
gym.displayFormattedReport();
```

---

## File Format

All files use **pipe-delimited format** (`|`) for easy parsing:
- Each record is one line
- Fields separated by `|`
- Easy to import/export to spreadsheets and databases
- Human-readable format

---

## Features

✅ **Save Records**: Append mode keeps previous records and adds new ones
✅ **Load Records**: Read and display all saved records with formatting
✅ **Formatted Display**: Clean, aligned output with borders and separators
✅ **Complete Backup**: GymController can save entire database at once
✅ **Error Handling**: Checks for file opening errors and displays messages
✅ **Consistent Format**: All classes follow same I/O pattern for easy use

---

## File Locations

Output files will be created in the project's working directory:
- `gym_backup.txt` - Complete gym data backup
- `members.txt` - Member records
- `trainers.txt` - Trainer records
- `payments.txt` - Payment records
- `attendance.txt` - Attendance records

---

## Next Steps

You can now:
1. Call `saveToFile()` on any object to persist data
2. Call `loadFromFile()` to display saved records
3. Call `displayFormatted()` to show records in clean format
4. Use `gym.saveAllDataToFile()` for complete backups
5. Use `gym.displayFormattedReport()` for system reports
