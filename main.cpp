#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "Person.h"
#include "Trainer.h"
#include "Payment.h"
#include "AttendanceRecord.h"
#include "gym.h"
#include "Exercise.h"
#include "WorkoutProgram.h"
#include "GymController.h"

using namespace std;
// loop stop helper - integers
int getValidInt(const string& prompt) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            size_t pos;
            value = stoi(input, &pos);
            if (pos != input.length()) throw invalid_argument("Extra characters");
            return value;
        } catch (...) {
            cout << "Invalid input. Please enter a valid integer.\n";
        }
    }
}

// loop stop helper - doubles
double getValidDouble(const string& prompt) {
    string input;
    double value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            size_t pos;
            value = stod(input, &pos);
            if (pos != input.length()) throw invalid_argument("Extra characters");
            if (value < 0) throw invalid_argument("Negative");
            return value;
        } catch (...) {
            cout << "Invalid input. Please enter a valid positive number.\n";
        }
    }
}
// ===== MENU DISPLAY HELPERS =====

void displayMainMenu() {
    cout << "\n============================================\n";
    cout << "     FITNESS GYM MANAGEMENT SYSTEM MENU\n";
    cout << "============================================\n";
    cout << "1. Member Management\n";
    cout << "2. Trainer Management\n";
    cout << "3. Payment Management\n";
    cout << "4. Attendance Management\n";
    cout << "5. Exercise Management\n";
    cout << "6. Workout Programs\n";
    cout << "7. Reports\n";
    cout << "8. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice (1-8): ";
}

void displayMemberMenu() {
    cout << "\n--- MEMBER MANAGEMENT ---\n";
    cout << "1. Add Member\n";
    cout << "2. Update Member\n";
    cout << "3. Search Member\n";
    cout << "4. Delete Member\n";
    cout << "5. Display All Members\n";
    cout << "6. Upgrade / Change Membership Plan\n";   // Fix 4
    cout << "7. Back to Main Menu\n";
    cout << "Enter choice (1-7): ";
}

void displayTrainerMenu() {
    cout << "\n--- TRAINER MANAGEMENT ---\n";
    cout << "1. Add Trainer\n";
    cout << "2. Remove Trainer\n";
    cout << "3. Search Trainer\n";
    cout << "4. Assign Trainer to Member\n";
    cout << "5. Display All Trainers\n";
    cout << "6. Back to Main Menu\n";
    cout << "Enter choice (1-6): ";
}

void displayPaymentMenu() {
    cout << "\n--- PAYMENT MANAGEMENT ---\n";
    cout << "1. Record Payment\n";
    cout << "2. Display All Payments\n";
    cout << "3. Track Unpaid Balances\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter choice (1-4): ";
}

void displayAttendanceMenu() {
    cout << "\n--- ATTENDANCE MANAGEMENT ---\n";
    cout << "1. Record Attendance\n";
    cout << "2. View Member Attendance History\n";
    cout << "3. Display All Attendance Records\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter choice (1-4): ";
}

void displayReportMenu() {
    cout << "\n--- REPORTS ---\n";
    cout << "1. Generate Full Report\n";
    cout << "2. Active Members Count\n";
    cout << "3. Monthly Revenue\n";
    cout << "4. Trainer Performance\n";
    cout << "5. Trainer Ranking\n";
    cout << "6. Most Popular Plan\n";
    cout << "7. Attendance Statistics\n";
    cout << "8. Expired Memberships\n";
    cout << "9. Back to Main Menu\n";
    cout << "Enter choice (1-9): ";
}

void displayExerciseMenu() {
    cout << "\n--- EXERCISE MANAGEMENT ---\n";
    cout << "1. Add Exercise\n";
    cout << "2. Display All Exercises\n";
    cout << "3. Remove Exercise\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter choice (1-4): ";
}

void displayWorkoutProgramMenu() {
    cout << "\n--- WORKOUT PROGRAM MANAGEMENT ---\n";
    cout << "1. Create Workout Program\n";
    cout << "2. Display All Programs\n";
    cout << "3. Add Exercise to Program\n";
    cout << "4. Remove Program\n";
    cout << "5. Back to Main Menu\n";
    cout << "Enter choice (1-5): ";
}

// ===== MEMBER MANAGEMENT =====
// Fix 5: Every user-facing operation is wrapped in try/catch so a bad input
//         (duplicate ID, underage, invalid plan, etc.) prints an error and
//         continues the menu instead of crashing.

void manageMember(GymController& gym) {
    while (true) {
        displayMemberMenu();
        int choice = getValidInt("");

        if (choice == 1) {
            // ── Add Member ──
            string name, gender, contact, plan, regDate, expDate, trainer;

            cout << "\n--- Add New Member ---\n";
            int id  = getValidInt("Member ID: ");
            cout << "Full Name: ";       getline(cin, name);
            int age = getValidInt("Age (min 18): ");
            cout << "Gender: ";          getline(cin, gender);
            cout << "Contact Info: ";    getline(cin, contact);
            cout << "Membership Plan (Basic / Premium / VIP / Personal Training): ";
            getline(cin, plan);
            cout << "Registration Date (DD/MM/YYYY): "; getline(cin, regDate);
            cout << "Expiration Date   (DD/MM/YYYY): "; getline(cin, expDate);
            cout << "Assigned Trainer (or 'None'): ";   getline(cin, trainer);

            // Fix 5: catch invalid_argument (age < 18) or runtime_error (duplicate ID)
            try {
                Member newMember(id, name, age, gender, contact, plan, regDate, expDate, trainer);
                gym.addMember(newMember);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }

        else if (choice == 2) {
            // ── Update Member ──
            string name, contact;

            cout << "\n--- Update Member ---\n";
            int id = getValidInt("Enter Member ID: ");
            cout << "New Name: ";        getline(cin, name);
            int age = getValidInt("New Age (min 18): ");
            cout << "New Contact Info: ";getline(cin, contact);

            try {
                gym.updateMember(id, name, age, contact);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }

        else if (choice == 3) {
            int id = getValidInt("\nEnter Member ID to search: ");
            gym.searchMember(id);
        }

        else if (choice == 4) {
            // ── Delete Member ──
            // Fix 1: deleteMember() now correctly blocks ACTIVE members
            int id = getValidInt("\nEnter Member ID to delete: ");
            gym.deleteMember(id);
        }

        else if (choice == 5) {
            gym.displayAllMembers();
        }

        else if (choice == 6) {
            // ── Fix 4: Upgrade / change plan using Membership hierarchy ──
            string newPlan;
            cout << "\n--- Change Membership Plan ---\n";
            int id = getValidInt("Member ID: ");
            cout << "New Plan (Basic / Premium / VIP / Personal Training): ";
            getline(cin, newPlan);

            try {
                gym.upgradeMemberPlan(id, newPlan);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }

        else if (choice == 7) {
            break;
        }

        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// ===== TRAINER MANAGEMENT =====

void manageTrainer(GymController& gym) {
    while (true) {
        displayTrainerMenu();
        int choice = getValidInt("");

        if (choice == 1) {
            double salary, commission;
            string name, contact, specialty;

            cout << "\n--- Add New Trainer ---\n";
            int id = getValidInt("Trainer ID: ");
            cout << "Name: ";        getline(cin, name);
            cout << "Contact: ";     getline(cin, contact);
            cout << "Specialty: ";   getline(cin, specialty);
            salary     = getValidDouble("Salary $: ");
            commission = getValidDouble("Commission %: ");

            // Fix 5: catch duplicate ID
            try {
                Trainer newTrainer(id, name, contact, specialty, salary, commission);
                gym.addTrainer(newTrainer);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }

        else if (choice == 2) {
            int id = getValidInt("\nEnter Trainer ID to remove: ");
            gym.removeTrainer(id);
        }

        else if (choice == 3) {
            int id = getValidInt("\nEnter Trainer ID to search: ");
            gym.searchTrainer(id);
        }

        else if (choice == 4) {
            cout << "\n--- Assign Trainer to Member ---\n";
            int trainerId = getValidInt("Trainer ID: ");
            int memberId  = getValidInt("Member ID: ");
            gym.assignTrainerToMember(trainerId, memberId);
        }

        else if (choice == 5) {
            gym.displayAllTrainers();
        }

        else if (choice == 6) {
            break;
        }

        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// ===== PAYMENT MANAGEMENT =====

void managePayment(GymController& gym) {
    while (true) {
        displayPaymentMenu();
        int choice = getValidInt("");

        if (choice == 1) {
            string memberID, date, notes;
            double amount, discount, penalty;

            cout << "\n--- Record New Payment ---\n";
            cout << "Member ID: ";   getline(cin, memberID);
            amount   = getValidDouble("Amount $: ");
            cout << "Date (DD/MM/YYYY): "; getline(cin, date);
            cout << "Payment Method:\n"
                    "  1. Cash  2. Credit Card  3. Debit Card  4. Bank Transfer  5. Online\n"
                    "Choose (1-5): ";
            int methodChoice = getValidInt("Choose (1-5): ");
            cout << "Status:\n"
                    "  1. Pending  2. Completed  3. Failed  4. Refunded\n";
            int statusChoice = getValidInt("Choose (1-4): ");
            discount = getValidDouble("Discount $: ");
            penalty  = getValidDouble("Penalty  $: ");
            cout << "Notes: ";      getline(cin, notes);

            // Fix 5: Payment setters already validate; wrap in try/catch for safety
            try {
                PaymentMethod method = static_cast<PaymentMethod>(methodChoice - 1);
                PaymentStatus status = static_cast<PaymentStatus>(statusChoice - 1);
                Payment payment(memberID, amount, date, method, status, discount, penalty, notes);
                gym.recordPayment(payment);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }

        else if (choice == 2) { gym.displayAllPayments();    }
        else if (choice == 3) { gym.trackUnpaidBalances();   }
        else if (choice == 4) { break; }
        else { cout << "Invalid choice.\n"; }
    }
}

// ===== ATTENDANCE MANAGEMENT =====

void manageAttendance(GymController& gym) {
    while (true) {
        displayAttendanceMenu();
        int choice = getValidInt("");

        if (choice == 1) {
            string memberID, date, checkInTime, checkOutTime;
            cout << "\n--- Record Attendance ---\n";
            cout << "Member ID: ";            getline(cin, memberID);
            cout << "Date (DD/MM/YYYY): ";    getline(cin, date);
            cout << "Check-In  Time (HH:MM): ";getline(cin, checkInTime);
            cout << "Check-Out Time (HH:MM): ";getline(cin, checkOutTime);

            AttendanceRecord record(memberID, date, checkInTime, checkOutTime);
            gym.recordAttendance(record);
        }

        else if (choice == 2) {
            int memberId = getValidInt("\nEnter Member ID: ");
            gym.displayAttendanceHistory(memberId);
        }

        else if (choice == 3) { gym.displayAllAttendance(); }
        else if (choice == 4) { break; }
        else { cout << "Invalid choice.\n"; }
    }
}

// ===== REPORTS =====

void viewReports(GymController& gym) {
    while (true) {
        displayReportMenu();
        int choice = getValidInt("");

        switch (choice) {
            case 1: gym.generateReport();              break;
            case 2: gym.displayTotalActiveMembers();   break;
            case 3: gym.displayMonthlyRevenue();       break;
            case 4: gym.displayTrainerPerformance();   break;
            case 5: gym.displayTrainerRanking();       break;
            case 6: gym.displayMostPopularPlan();      break;
            case 7: gym.displayAttendanceStatistics(); break;
            case 8: gym.displayExpiredMemberships();   break;
            case 9: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

// ===== EXERCISE MANAGEMENT =====

void manageExercise(GymController& gym) {
    while (true) {
        displayExerciseMenu();
        int choice = getValidInt("");

        if (choice == 1) {
            string name;
            cout << "\nExercise Name: "; getline(cin, name);
            int sets     = getValidInt("Sets: ");
            int reps     = getValidInt("Reps: ");
            int restTime = getValidInt("Rest Time (seconds): ");

            // Fix 5: Exercise setters validate positive values
            try {
                Exercise ex(name, sets, reps, restTime);
                gym.addExercise(ex);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (choice == 2) { gym.displayAllExercises(); }
        else if (choice == 3) {
            gym.displayAllExercises();
            int index = getValidInt("Enter exercise index to remove: ");
            gym.removeExercise(index);
        }
        else if (choice == 4) { break; }
        else { cout << "Invalid choice.\n"; }
    }
}

// ===== WORKOUT PROGRAM MANAGEMENT =====

void manageWorkoutProgram(GymController& gym) {
    while (true) {
        displayWorkoutProgramMenu();
        int choice = getValidInt("");

        if (choice == 1) {
            string name, targetGoal, duration, assignedTrainer;
            int programID = getValidInt("\nProgram ID: ");
            cout << "Program Name: "; getline(cin, name);
            cout << "Target Goal (Weight Loss / Muscle Gain / etc.): "; getline(cin, targetGoal);
            cout << "Duration (e.g. 8 weeks): "; getline(cin, duration);
            cout << "Assigned Trainer: "; getline(cin, assignedTrainer);

            WorkoutProgram program(programID, name, targetGoal, duration, assignedTrainer);
            gym.addWorkoutProgram(program);
        }
        else if (choice == 2) { gym.displayAllWorkoutPrograms(); }
        else if (choice == 3) {
            gym.displayAllWorkoutPrograms();
            int programIndex = getValidInt("Program index: ");

            string exerciseName; int sets, reps, restTime;
            cout << "Exercise Name: "; getline(cin, exerciseName);
            sets     = getValidInt("Sets: ");
            reps     = getValidInt("Reps: ");
            restTime = getValidInt("Rest Time (seconds): ");

            Exercise ex(exerciseName, sets, reps, restTime);
            gym.addExerciseToProgram(programIndex, ex);
        }
        else if (choice == 4) {
            gym.displayAllWorkoutPrograms();
            int programIndex = getValidInt("Program index to remove: ");
            gym.removeWorkoutProgram(programIndex);
        }
        else if (choice == 5) { break; }
        else { cout << "Invalid choice.\n"; }
    }
}

// ===== MAIN =====

int main() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║    FITNESS / GYM MANAGEMENT SYSTEM v1.0                 ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";

    GymController gym;

    // Fix 5: Wrap startup load in try/catch
    try {
        gym.loadAllDataFromFile("gym_data.txt");
    } catch (const exception& e) {
        cout << "Warning on load: " << e.what() << endl;
    }

    cout << "✓ System initialized successfully!\n";
    cout << "✓ Ready for operations.\n\n";

    bool running = true;

    while (running) {
        displayMainMenu();
        int mainChoice = getValidInt("");

        // Fix 5: Top-level catch so ANY unexpected exception never crashes the program
        try {
            switch (mainChoice) {
                case 1: manageMember(gym);        break;
                case 2: manageTrainer(gym);       break;
                case 3: managePayment(gym);       break;
                case 4: manageAttendance(gym);    break;
                case 5: manageExercise(gym);      break;
                case 6: manageWorkoutProgram(gym);break;
                case 7: viewReports(gym);         break;
                case 8:
                    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
                    cout << "║    Thank you for using Fitness Gym Management System!     ║\n";
                    cout << "║              All data has been saved.                     ║\n";
                    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
                    gym.saveAllDataToFile("gym_data.txt");
                    running = false;
                    break;
                default:
                    cout << "Invalid choice. Enter a number between 1 and 8.\n";
            }
        } catch (const exception& e) {
            // Catches anything the sub-menus didn't already handle
            cout << "Unexpected error: " << e.what() << endl;
        }
    }

    return 0;
}
