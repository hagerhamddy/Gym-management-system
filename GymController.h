#ifndef GYMCONTROLLER_H
#define GYMCONTROLLER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include "Person.h"
#include "Trainer.h"
#include "Payment.h"
#include "AttendanceRecord.h"
#include "gym.h"
#include "Member.h"
#include "Exercise.h"
#include "WorkoutProgram.h"

using namespace std;

class GymController {
private:
    vector<Member>          members;
    vector<Trainer>         trainers;
    vector<Payment>         payments;
    vector<AttendanceRecord>attendanceRecords;
    vector<Exercise>        exercises;
    vector<WorkoutProgram>  workoutPrograms;
    vector<Membership*>     membershipPlans;   // owns heap Membership objects
    static const string     DATA_FILE;

public:
    GymController();
    ~GymController();

    // ===== MEMBER MANAGEMENT =====
    void addMember(const Member& member);       // throws on duplicate ID
    void deleteMember(int id);                  // blocks active members (fixed)
    void updateMember(int id, string newName, int age, string contact);
    void searchMember(int id) const;
    void displayAllMembers() const;
    void upgradeMemberPlan(int memberId, const string& newPlan); // Fix 4: uses Membership hierarchy

    // ===== TRAINER MANAGEMENT =====
    void addTrainer(const Trainer& trainer);    // throws on duplicate ID
    void removeTrainer(int id);
    void assignTrainerToMember(int trainerId, int memberId);
    void displayAllTrainers() const;
    void searchTrainer(int id) const;

    // ===== PAYMENT MANAGEMENT =====
    void recordPayment(const Payment& payment);
    void displayAllPayments() const;
    void trackUnpaidBalances() const;

    // ===== ATTENDANCE MANAGEMENT =====
    void recordAttendance(const AttendanceRecord& record);
    void displayAttendanceHistory(int memberId) const;
    void displayAllAttendance() const;

    // ===== EXERCISE MANAGEMENT =====
    void addExercise(const Exercise& exercise);
    void removeExercise(int exerciseIndex);
    void displayAllExercises() const;

    // ===== WORKOUT PROGRAM MANAGEMENT =====
    void addWorkoutProgram(const WorkoutProgram& program);
    void removeWorkoutProgram(int programIndex);
    void displayAllWorkoutPrograms() const;
    void addExerciseToProgram(int programIndex, const Exercise& exercise);

    // ===== REPORT GENERATION =====
    void generateReport() const;
    void displayTotalActiveMembers() const;
    void displayExpiredMemberships() const;
    void displayMonthlyRevenue() const;
    void displayTrainerPerformance() const;
    void displayTrainerRanking() const;
    void displayMostPopularPlan() const;
    void displayAttendanceStatistics() const;

    // ===== I/O FUNCTIONS =====
    void saveAllDataToFile(const string& filename) const;
    void loadAllDataFromFile(const string& filename);
    void displayFormattedReport() const;
};

#endif // GYMCONTROLLER_H
