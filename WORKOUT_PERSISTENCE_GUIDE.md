# Workout Programs & Exercises Persistence Guide

## Overview
This document explains the new persistent data storage system implemented for **Exercises** and **Workout Programs** in the Gym Management System. All workout data is now automatically saved to `gym_data.txt` and reloaded when the program starts, similar to how Members, Trainers, Payments, and Attendance Records are managed.

---

## What Was Added

### 1. **New Classes & Components**

#### GymController Enhancements
Added two new private vectors to store exercises and workout programs:
```cpp
vector<Exercise> exercises;              // Stores all exercises
vector<WorkoutProgram> workoutPrograms;  // Stores all workout programs
```

#### New Methods in GymController
- **Exercise Management:**
  - `void addExercise(const Exercise& exercise)` - Add a new exercise
  - `void removeExercise(int exerciseIndex)` - Remove an exercise by index
  - `void displayAllExercises() const` - Display all saved exercises

- **Workout Program Management:**
  - `void addWorkoutProgram(const WorkoutProgram& program)` - Add a new program
  - `void removeWorkoutProgram(int programIndex)` - Remove a program by index
  - `void displayAllWorkoutPrograms() const` - Display all programs with their exercises
  - `void addExerciseToProgram(int programIndex, const Exercise& exercise)` - Add exercises to programs

---

### 2. **Data File Format** 

The `gym_data.txt` file now includes two new sections:

#### Exercises Section
```
=== EXERCISES ===
ExerciseName|Sets|Reps|RestTime
Bench Press|4|8|120
Squats|3|10|90
Deadlift|5|5|180
```
**Format:** `ExerciseName|Sets|Reps|RestTime(in seconds)`

#### Workout Programs Section
```
=== WORKOUT_PROGRAMS ===
ProgramID|Name|Goal|Duration|Trainer|ExerciseCount
1|Summer Shred|Weight Loss|8 weeks|John Smith|3
  Bench Press|4|8|120
  Squats|3|10|90
  Cardio|1|20|0
2|Bulk Up|Muscle Gain|12 weeks|Mike Johnson|2
  Deadlift|5|5|180
  Pull-ups|4|6|120
```
**Format:**
- Program Header: `ProgramID|Name|Goal|Duration|Trainer|ExerciseCount`
- Exercise Lines (indented with 2 spaces): `  ExerciseName|Sets|Reps|RestTime`

---

### 3. **Auto-Save Functionality**

Every time you:
- ✅ Add an exercise
- ✅ Remove an exercise
- ✅ Create a workout program
- ✅ Add an exercise to a program
- ✅ Remove a workout program

**The system automatically saves all data to `gym_data.txt`**

---

### 4. **Auto-Load Functionality**

When you start the program:
1. GymController is initialized
2. `loadAllDataFromFile("gym_data.txt")` is called automatically
3. All previous exercises and workout programs are restored
4. A summary shows how many items were loaded:
   ```
   Data loaded successfully!
     - Members: 5
     - Trainers: 2
     - Payments: 12
     - Attendance Records: 45
     - Exercises: 8
     - Workout Programs: 3
   ```

---

### 5. **New Menu Options**

#### Main Menu (Updated)
```
1. Member Management
2. Trainer Management
3. Payment Management
4. Attendance Management
5. Exercise Management        ← NEW
6. Workout Programs           
7. Reports
8. Exit
```

#### Exercise Management Menu (NEW)
```
--- EXERCISE MANAGEMENT ---
1. Add Exercise
2. Display All Exercises
3. Remove Exercise
4. Back to Main Menu
```

**Process:**
1. Select "5. Exercise Management" from main menu
2. Choose an option to add, view, or remove exercises
3. All changes are automatically saved

#### Workout Program Management Menu (NEW)
```
--- WORKOUT PROGRAM MANAGEMENT ---
1. Create Workout Program
2. Display All Programs
3. Add Exercise to Program
4. Remove Program
5. Back to Main Menu
```

**Process:**
1. Select "6. Workout Programs" from main menu
2. Create programs with name, goal, duration, and trainer
3. Add exercises to programs
4. View all programs with their complete exercise lists
5. All changes persist after program restart

---

## Usage Example

### Adding an Exercise
```
Main Menu → 5. Exercise Management → 1. Add Exercise
Enter exercise details:
Exercise Name: Bench Press
Sets: 4
Reps: 8
Rest Time (seconds): 120
✓ Exercise added successfully: Bench Press
✓ Data automatically saved to gym_data.txt
```

### Creating a Workout Program
```
Main Menu → 6. Workout Programs → 1. Create Workout Program
Enter workout program details:
Program ID: 1
Program Name: Summer Shred
Target Goal (e.g., Weight Loss, Muscle Gain): Weight Loss
Duration (e.g., 8 weeks): 8 weeks
Assigned Trainer: John Smith
✓ Workout program added successfully: Summer Shred
✓ Data automatically saved to gym_data.txt
```

### Adding Exercise to Program
```
Main Menu → 6. Workout Programs → 3. Add Exercise to Program
[Displays all programs with indexes]
Enter program index to add exercise to: 0
Exercise Name: Bench Press
Sets: 4
Reps: 8
Rest Time (seconds): 120
✓ Exercise added to program
✓ Data automatically saved to gym_data.txt
```

### Viewing Saved Data on Program Restart
```
$ ./app

FITNESS / GYM MANAGEMENT SYSTEM v1.0

Data loaded successfully!
  - Members: 5
  - Trainers: 2
  - Payments: 12
  - Attendance Records: 45
  - Exercises: 8              ← Exercises loaded!
  - Workout Programs: 3       ← Programs loaded!

System initialized successfully!
Ready for operations.
```

---

## Data Persistence Flow

```
User Creates Exercise/Program
         ↓
GymController Method Called
         ↓
Data Added to Vector
         ↓
saveAllDataToFile() Triggered
         ↓
gym_data.txt Updated
         ↓
         ↓ [Program Restarts]
         ↓
loadAllDataFromFile() Called
         ↓
Data Parsed & Restored
         ↓
All Previous Data Available
```

---

## File Structure Integration

The persistence system integrates seamlessly with existing code:

| Feature | Status |
|---------|--------|
| Members | ✅ Existing + Working |
| Trainers | ✅ Existing + Working |
| Payments | ✅ Existing + Working |
| Attendance | ✅ Existing + Working |
| **Exercises** | ✅ **NEW - Fully Integrated** |
| **Workout Programs** | ✅ **NEW - Fully Integrated** |

---

## Important Notes

1. **No Manual Save Required** - All data saves automatically
2. **No File Creation Needed** - `gym_data.txt` is created automatically
3. **Full Persistence** - Exercise details include sets, reps, and rest time
4. **Program Organization** - Exercises are saved with their parent programs
5. **Data Integrity** - Invalid data lines are skipped during loading
6. **Backward Compatible** - Existing members/trainers/payments still work perfectly

---

## Modified Files

### New Additions
- GymController.h - Added vectors and method declarations
- GymController.cpp - Implemented exercise/program management and persistence logic
- main.cpp - Added menu functions and integrated with main loop

### Features Added
- Exercise Management subsystem
- Workout Program Management subsystem
- Auto-save/load for exercises and programs
- New menu options and user interface

---

## Example Data File (gym_data.txt)

```
=== MEMBERS ===
1|John Doe|30|Male|555-1234|Basic|01/01/2024|12/31/2024|None|Active

=== TRAINERS ===
1|Smith|555-5678|Cardio|45000.00|5

=== PAYMENTS ===
PAY001|1|500.00|01/01/2024|Cash|Completed|0|0

=== ATTENDANCE ===
1|01/15/2024|06:00|08:30

=== EXERCISES ===
Bench Press|4|8|120
Squats|3|10|90
Deadlift|5|5|180

=== WORKOUT_PROGRAMS ===
1|Summer Shred|Weight Loss|8 weeks|John Smith|3
  Bench Press|4|8|120
  Squats|3|10|90
  Cardio|1|20|0
```

---

## Testing the New Features

1. **Start the program**: `./app`
2. **Add some exercises**: Main Menu → 5 → 1
3. **Create a program**: Main Menu → 6 → 1
4. **Add exercises to program**: Main Menu → 6 → 3
5. **Exit the program**: Main Menu → 8
6. **Restart the program**: `./app`
7. **Verify persistence**: Main Menu → 5 → 2 (exercises still there!) or Main Menu → 6 → 2 (programs still there!)

✅ **If you see your data loaded, persistence is working correctly!**

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Data not saving | Check file permissions, ensure `gym_data.txt` is in the same directory as the executable |
| Data not loading on startup | Verify `gym_data.txt` exists and contains proper formatting |
| Program crashes on load | Check for corrupted data in `gym_data.txt` |
| Exercises/Programs not showing | Make sure you added them before viewing (no default test data) |

---

## Summary

✅ **Exercises and Workout Programs now persist between program runs**
✅ **Automatic save after every modification**
✅ **Automatic load on startup**
✅ **Integrated with existing data management system**
✅ **User-friendly menu system**
✅ **Full data integrity checks**

Your fitness gym management system now has complete persistence for all workout-related data! 🏋️
