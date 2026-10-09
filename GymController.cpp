#include "GymController.h"
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

#if __has_include(<stdexcept>)
    #include <stdexcept>
#else
    #include <exception>
#endif

const string GymController::DATA_FILE = "gym_data.txt";

GymController::GymController() {}

GymController::~GymController() {
    for (auto plan : membershipPlans) {
        delete plan;
    }
    membershipPlans.clear();
}

// ===== MEMBER MANAGEMENT =====

void GymController::addMember(const Member& member) {
    // ── Fix 3: Duplicate ID check ──
    for (const auto& m : members) {
        if (m.getID() == member.getID()) {
            throw runtime_error(
                "Error: A member with ID " + to_string(member.getID()) + " already exists.");
        }
    }
    members.push_back(member);
    cout << "Member added successfully: " << member.getName() << endl;
    saveAllDataToFile(DATA_FILE);
}

void GymController::deleteMember(int id) {
    for (int i = 0; i < (int)members.size(); i++) {
        if (members[i].getID() == id) {

            // ── Fix 1: Corrected logic — block deletion of ACTIVE members ──
            // getStatus() returns true  → member IS active  → block it
            // getStatus() returns false → member is expired → allow deletion
            if (members[i].getStatus()) {
                cout << "Cannot delete active member. Deactivate membership first.\n";
                return;
            }

            cout << "Deleted member: " << members[i].getName() << endl;
            members.erase(members.begin() + i);
            saveAllDataToFile(DATA_FILE);
            return;
        }
    }
    cout << "Member not found.\n";
}

void GymController::updateMember(int id, string newName, int age, string contact) {
    for (int i = 0; i < (int)members.size(); i++) {
        if (members[i].getID() == id) {
            // updateInfo() now throws if age < 18 (Fix 9)
            members[i].updateInfo(newName, age, contact);
            cout << "Member updated successfully.\n";
            saveAllDataToFile(DATA_FILE);
            return;
        }
    }
    cout << "Member not found.\n";
}

void GymController::searchMember(int id) const {
    for (const auto& member : members) {
        if (member.getID() == id) {
            member.displayDetails();   // calls the pure-virtual override (Fix 8)
            return;
        }
    }
    cout << "Member not found.\n";
}

void GymController::displayAllMembers() const {
    if (members.empty()) {
        cout << "No members found.\n";
        return;
    }
    cout << "\n========== ALL MEMBERS ==========\n";
    for (const auto& member : members) {
        cout << "ID: " << member.getID()
             << " | Name: " << member.getName()
             << " | Status: " << (member.getStatus() ? "Active" : "Expired") << endl;
    }
}

// ── Fix 4 helper: upgrade a member's plan from the menu ──
void GymController::upgradeMemberPlan(int memberId, const string& newPlan) {
    for (auto& m : members) {
        if (m.getID() == memberId) {
            m.upgradePlan(newPlan);          // Member uses Membership hierarchy internally
            m.displayPlanDetails();          // shows the new plan's details via subclass
            saveAllDataToFile(DATA_FILE);
            return;
        }
    }
    cout << "Member not found.\n";
}

// ===== TRAINER MANAGEMENT =====

void GymController::addTrainer(const Trainer& trainer) {
    // ── Fix 3: Duplicate ID check ──
    for (const auto& t : trainers) {
        if (t.getId() == trainer.getId()) {
            throw runtime_error(
                "Error: A trainer with ID " + to_string(trainer.getId()) + " already exists.");
        }
    }
    trainers.push_back(trainer);
    saveAllDataToFile(DATA_FILE);
    cout << "Trainer added successfully.\n";
}

void GymController::removeTrainer(int id) {
    for (int i = 0; i < (int)trainers.size(); i++) {
        if (trainers[i].getId() == id) {
            cout << "Trainer removed: " << trainers[i].getName() << endl;
            trainers.erase(trainers.begin() + i);
            saveAllDataToFile(DATA_FILE);
            return;
        }
    }
    cout << "Trainer not found.\n";
}

void GymController::assignTrainerToMember(int trainerId, int memberId) {
    Trainer* trainerPtr = nullptr;
    Member*  memberPtr  = nullptr;

    for (auto& trainer : trainers) {
        if (trainer.getId() == trainerId) { trainerPtr = &trainer; break; }
    }
    for (auto& member : members) {
        if (member.getID() == memberId) { memberPtr = &member; break; }
    }

    if (!trainerPtr || !memberPtr) {
        cout << "Trainer or Member not found.\n";
        return;
    }

    const int MAX_MEMBERS_PER_TRAINER = 10;
    if ((int)trainerPtr->getAssignedMembers().size() >= MAX_MEMBERS_PER_TRAINER) {
        cout << "Error: Trainer " << trainerPtr->getName()
             << " has reached the maximum of " << MAX_MEMBERS_PER_TRAINER << " members.\n";
        return;
    }

    if (!memberPtr->getStatus()) {
        cout << "Error: Cannot assign trainer to a member with expired membership.\n";
        return;
    }

    trainerPtr->addMember(memberId);
    memberPtr->assignTrainer(trainerPtr->getName());
    saveAllDataToFile(DATA_FILE);
    cout << "Trainer assigned to member successfully.\n";
}

void GymController::displayAllTrainers() const {
    if (trainers.empty()) { cout << "No trainers found.\n"; return; }
    cout << "\n========== ALL TRAINERS ==========\n";
    for (const auto& trainer : trainers) {
        trainer.displayDetails();   // pure-virtual override in Trainer (Fix 8)
    }
}

void GymController::searchTrainer(int id) const {
    for (const auto& trainer : trainers) {
        if (trainer.getId() == id) {
            trainer.displayDetails();
            return;
        }
    }
    cout << "Trainer not found.\n";
}

// ===== PAYMENT MANAGEMENT =====

void GymController::recordPayment(const Payment& payment) {
    payments.push_back(payment);

    // ── Fix 7: Update the member's own payment history ──
    for (auto& m : members) {
        if (to_string(m.getID()) == payment.getMemberID()) {
            m.addPayment(payment.getPaymentID() + " | $" +
                         to_string(payment.getFinalAmount()) + " | " +
                         payment.getDate() + " | " + payment.getStatusStr());
            break;
        }
    }

    saveAllDataToFile(DATA_FILE);
    cout << "Payment recorded.\n";
    payment.displayReceipt();
}

void GymController::displayAllPayments() const {
    if (payments.empty()) { cout << "No payments found.\n"; return; }
    cout << "\n========== ALL PAYMENTS ==========\n";
    for (const auto& payment : payments) {
        payment.displayReceipt();
    }
}

void GymController::trackUnpaidBalances() const {
    cout << "\n========== UNPAID BALANCES ==========\n";
    double totalUnpaid = 0.0;
    int    count       = 0;
    for (const auto& payment : payments) {
        if (payment.isUnpaid()) {
            cout << "Member: " << payment.getMemberID()
                 << " | Amount: $" << payment.getFinalAmount()
                 << " | Status: "  << payment.getStatusStr() << endl;
            totalUnpaid += payment.getFinalAmount();
            count++;
        }
    }
    if (count == 0) cout << "No unpaid balances.\n";
    else cout << "Total Unpaid Count: " << count << " | Total: $" << totalUnpaid << endl;
}

// ===== ATTENDANCE MANAGEMENT =====

void GymController::recordAttendance(const AttendanceRecord& record) {
    // Block expired members
    for (const auto& member : members) {
        if (to_string(member.getID()) == record.getMemberID()) {
            if (!member.getStatus()) {
                cout << "Error: Member " << record.getMemberID()
                     << " has an expired membership. Cannot record attendance.\n";
                return;
            }
            break;
        }
    }

    // Prevent duplicate check-in (same member, same date)
    for (const auto& existing : attendanceRecords) {
        if (existing.getMemberID() == record.getMemberID() &&
            existing.getDate()     == record.getDate()) {
            cout << "Error: Member " << record.getMemberID()
                 << " already checked in on " << record.getDate() << ".\n";
            return;
        }
    }

    attendanceRecords.push_back(record);

    // ── Fix 7: Update the member's own attendance history ──
    for (auto& m : members) {
        if (to_string(m.getID()) == record.getMemberID()) {
            m.addAttendance(record.getDate() + " in:" + record.getCheckInTime() +
                            " out:" + record.getCheckOutTime());
            break;
        }
    }

    saveAllDataToFile(DATA_FILE);
    cout << "Attendance recorded for member: " << record.getMemberID() << endl;
}

void GymController::displayAttendanceHistory(int memberId) const {
    cout << "\n========== ATTENDANCE HISTORY - MEMBER " << memberId << " ==========\n";
    bool found = false;
    for (const auto& record : attendanceRecords) {
        if (stoi(record.getMemberID()) == memberId) {
            record.displayAttendance();
            found = true;
        }
    }
    if (!found) cout << "No attendance records found for this member.\n";
}

void GymController::displayAllAttendance() const {
    if (attendanceRecords.empty()) { cout << "No attendance records.\n"; return; }
    cout << "\n========== ALL ATTENDANCE RECORDS ==========\n";
    for (const auto& record : attendanceRecords) {
        record.displayAttendance();
    }
}

// ===== EXERCISE MANAGEMENT =====

void GymController::addExercise(const Exercise& exercise) {
    exercises.push_back(exercise);
    cout << "Exercise added successfully: " << exercise.getExerciseName() << endl;
    saveAllDataToFile(DATA_FILE);
}

void GymController::removeExercise(int exerciseIndex) {
    if (exerciseIndex >= 0 && exerciseIndex < (int)exercises.size()) {
        cout << "Exercise removed: " << exercises[exerciseIndex].getExerciseName() << endl;
        exercises.erase(exercises.begin() + exerciseIndex);
        saveAllDataToFile(DATA_FILE);
    } else {
        cout << "Invalid exercise index.\n";
    }
}

void GymController::displayAllExercises() const {
    if (exercises.empty()) { cout << "No exercises available.\n"; return; }
    cout << "\n========== ALL EXERCISES ==========\n";
    for (int i = 0; i < (int)exercises.size(); i++) {
        cout << "Index " << i << ": ";
        exercises[i].displayExercise();
    }
    cout << "====================================\n";
}

// ===== WORKOUT PROGRAM MANAGEMENT =====

void GymController::addWorkoutProgram(const WorkoutProgram& program) {
    workoutPrograms.push_back(program);
    cout << "Workout program added: " << program.getName() << endl;
    saveAllDataToFile(DATA_FILE);
}

void GymController::removeWorkoutProgram(int programIndex) {
    if (programIndex >= 0 && programIndex < (int)workoutPrograms.size()) {
        cout << "Program removed: " << workoutPrograms[programIndex].getName() << endl;
        workoutPrograms.erase(workoutPrograms.begin() + programIndex);
        saveAllDataToFile(DATA_FILE);
    } else {
        cout << "Invalid program index.\n";
    }
}

void GymController::displayAllWorkoutPrograms() const {
    if (workoutPrograms.empty()) { cout << "No workout programs available.\n"; return; }
    cout << "\n========== ALL WORKOUT PROGRAMS ==========\n";
    for (int i = 0; i < (int)workoutPrograms.size(); i++) {
        cout << "Index " << i << ":\n";
        workoutPrograms[i].displayProgram();
        cout << endl;
    }
    cout << "==========================================\n";
}

void GymController::addExerciseToProgram(int programIndex, const Exercise& exercise) {
    if (programIndex >= 0 && programIndex < (int)workoutPrograms.size()) {
        workoutPrograms[programIndex].addExercise(exercise);
        saveAllDataToFile(DATA_FILE);
    } else {
        cout << "Invalid program index.\n";
    }
}

// ===== REPORT GENERATION =====

void GymController::generateReport() const {
    cout << "\n========== GYM SYSTEM REPORT ==========\n";
    displayTotalActiveMembers();    cout << endl;
    displayExpiredMemberships();    cout << endl;
    displayMonthlyRevenue();        cout << endl;
    displayTrainerPerformance();    cout << endl;
    displayTrainerRanking();        cout << endl;
    displayMostPopularPlan();       cout << endl;
    displayAttendanceStatistics();
}

void GymController::displayExpiredMemberships() const {
    cout << "\n========== EXPIRED MEMBERSHIPS ==========\n";
    int count = 0;
    for (const auto& member : members) {
        if (!member.getStatus()) {
            cout << "ID: " << member.getID()
                 << " | Name: " << member.getName()
                 << " | Expired: " << member.getExpirationDate() << endl;
            count++;
        }
    }
    if (count == 0) cout << "No expired memberships.\n";
    else            cout << "Total Expired: " << count << endl;
}

void GymController::displayTotalActiveMembers() const {
    int count = 0;
    for (const auto& m : members) { if (m.getStatus()) count++; }
    cout << "Total Active Members: " << count << " / " << members.size() << endl;
}

void GymController::displayMonthlyRevenue() const {
    cout << "Enter month to report (MM/YYYY, e.g. 05/2026): ";
    string monthFilter;
    cin >> monthFilter;
    cin.ignore();

    double revenue = 0.0;
    int    count   = 0;
    for (const auto& payment : payments) {
        string payDate  = payment.getDate();
        string payMonth = (payDate.size() >= 7) ? payDate.substr(3, 7) : "";
        if (payment.getStatus() == PaymentStatus::Completed && payMonth == monthFilter) {
            revenue += payment.getFinalAmount();
            count++;
        }
    }
    cout << "Monthly Revenue for " << monthFilter << ": $" << revenue
         << " (" << count << " completed payments)" << endl;
}

void GymController::displayTrainerPerformance() const {
    cout << "\n========== TRAINER PERFORMANCE ==========\n";
    for (const auto& trainer : trainers) {
        cout << "- " << trainer.getName() << ": "
             << trainer.getAssignedMembers().size() << " members assigned" << endl;
    }
}

void GymController::displayTrainerRanking() const {
    if (trainers.empty()) { cout << "No trainers found.\n"; return; }
    cout << "\n========== TRAINER RANKING (BY MEMBERS) ==========\n";

    vector<string> rankedNames;
    vector<int>    rankedCounts;
    for (const auto& trainer : trainers) {
        rankedNames.push_back(trainer.getName());
        rankedCounts.push_back(trainer.getAssignedMembers().size());
    }

    // Bubble sort descending
    for (int i = 0; i < (int)rankedNames.size(); i++) {
        for (int j = 0; j < (int)rankedNames.size() - i - 1; j++) {
            if (rankedCounts[j] < rankedCounts[j + 1]) {
                swap(rankedCounts[j], rankedCounts[j + 1]);
                swap(rankedNames[j],  rankedNames[j + 1]);
            }
        }
    }

    for (int i = 0; i < (int)rankedNames.size(); i++) {
        cout << (i + 1) << ". " << rankedNames[i]
             << " - " << rankedCounts[i] << " members" << endl;
    }
}

void GymController::displayMostPopularPlan() const {
    if (members.empty()) { cout << "No members found.\n"; return; }
    cout << "\n========== MOST POPULAR MEMBERSHIP PLAN ==========\n";

    map<string, int> planMap;
    for (const auto& member : members)
        planMap[member.getMembershipPlan()]++;

    string mostPopular;
    int    maxCount = 0;
    for (const auto& pair : planMap)
        if (pair.second > maxCount) { maxCount = pair.second; mostPopular = pair.first; }

    cout << "Most Popular Plan: " << mostPopular << " (" << maxCount << " members)\n";
    cout << "\nAll Plans Breakdown:\n";
    for (const auto& pair : planMap)
        cout << "  - " << pair.first << ": " << pair.second << " members\n";
}

void GymController::displayAttendanceStatistics() const {
    if (attendanceRecords.empty()) { cout << "No attendance records found.\n"; return; }
    cout << "\n========== ATTENDANCE STATISTICS ==========\n";
    cout << "Total Attendance Records: " << attendanceRecords.size() << endl;

    unordered_map<string, int> visitMap;
    for (const auto& record : attendanceRecords)
        visitMap[record.getMemberID()]++;

    cout << "Unique Members with Attendance: " << visitMap.size() << endl;

    double avgVisits = (double)attendanceRecords.size() / visitMap.size();
    cout << "Average Visits per Member: " << avgVisits << endl;

    string mostActive;
    int    maxV = 0;
    for (const auto& pair : visitMap)
        if (pair.second > maxV) { maxV = pair.second; mostActive = pair.first; }
    cout << "Most Active Member ID: " << mostActive << " (" << maxV << " visits)\n";

    cout << "\nEnter month to count visits (MM/YYYY, e.g. 05/2026): ";
    string monthFilter;
    cin >> monthFilter;
    cin.ignore();
    int monthlyCount = 0;
    for (const auto& record : attendanceRecords) {
        string d = record.getDate();
        if (d.size() >= 7 && d.substr(3, 7) == monthFilter)
            monthlyCount++;
    }
    cout << "Visits in " << monthFilter << ": " << monthlyCount << endl;

    cout << "\n--- Inactive Members (no attendance on record) ---\n";
    int inactiveCount = 0;
    for (const auto& member : members) {
        string mid = to_string(member.getID());
        if (visitMap.find(mid) == visitMap.end()) {
            cout << "  ID: " << member.getID()
                 << " | Name: " << member.getName() << " | INACTIVE\n";
            inactiveCount++;
        }
    }
    if (inactiveCount == 0) cout << "  All members have attendance records.\n";
}

// ===== I/O FUNCTIONS =====

void GymController::saveAllDataToFile(const string& filename) const {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cout << "Error: Could not save data to " << filename << endl;
        return;
    }

    file << "=== MEMBERS ===" << endl;
    for (const auto& member : members) {
        file << member.getID()              << "|" << member.getName()            << "|"
             << member.getAge()             << "|" << member.getGender()          << "|"
             << member.getContactInfo()     << "|" << member.getMembershipPlan()  << "|"
             << member.getRegistrationDate()<< "|" << member.getExpirationDate()  << "|"
             << member.getAssignedTrainer() << "|"
             << (member.getStatus() ? "Active" : "Inactive") << endl;
    }

    file << "=== TRAINERS ===" << endl;
    for (const auto& trainer : trainers) {
        file << trainer.getId()          << "|" << trainer.getName()       << "|"
             << trainer.getContactInfo() << "|" << trainer.getSpecialty()  << "|"
             << trainer.getSalary()      << "|" << trainer.getAssignedMembers().size() << endl;
    }

    file << "=== PAYMENTS ===" << endl;
    for (const auto& payment : payments) {
        file << payment.getPaymentID() << "|" << payment.getMemberID()  << "|"
             << payment.getAmount()    << "|" << payment.getDate()       << "|"
             << payment.getMethodStr() << "|" << payment.getStatusStr()  << "|"
             << payment.getDiscount()  << "|" << payment.getPenalty()    << endl;
    }

    file << "=== ATTENDANCE ===" << endl;
    for (const auto& record : attendanceRecords) {
        file << record.getMemberID()    << "|" << record.getDate()         << "|"
             << record.getCheckInTime() << "|" << record.getCheckOutTime() << endl;
    }

    file << "=== EXERCISES ===" << endl;
    for (const auto& exercise : exercises) {
        file << exercise.getExerciseName() << "|" << exercise.getSets()    << "|"
             << exercise.getReps()         << "|" << exercise.getRestTime()<< endl;
    }

    file << "=== WORKOUT_PROGRAMS ===" << endl;
    for (const auto& program : workoutPrograms) {
        file << program.getProgramID()    << "|" << program.getName()           << "|"
             << program.getTargetGoal()   << "|" << program.getDuration()       << "|"
             << program.getAssignedTrainer() << "|" << program.getExerciseList().size() << endl;
        for (const auto& exercise : program.getExerciseList()) {
            file << "  " << exercise.getExerciseName() << "|" << exercise.getSets()    << "|"
                 << exercise.getReps()                 << "|" << exercise.getRestTime()<< endl;
        }
    }

    file.close();
    cout << "All gym data saved to " << filename << endl;
}

void GymController::loadAllDataFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    cout << "\nLoading data from " << filename << "...\n";
    string line;
    string currentSection = "";

    while (getline(file, line)) {
        if (line.empty()) continue;

        if      (line.find("=== MEMBERS ===")          != string::npos) { currentSection = "MEMBERS";          continue; }
        else if (line.find("=== TRAINERS ===")          != string::npos) { currentSection = "TRAINERS";         continue; }
        else if (line.find("=== PAYMENTS ===")          != string::npos) { currentSection = "PAYMENTS";         continue; }
        else if (line.find("=== ATTENDANCE ===")        != string::npos) { currentSection = "ATTENDANCE";       continue; }
        else if (line.find("=== EXERCISES ===")         != string::npos) { currentSection = "EXERCISES";        continue; }
        else if (line.find("=== WORKOUT_PROGRAMS ===")  != string::npos) { currentSection = "WORKOUT_PROGRAMS"; continue; }

        // Helper lambda to split a line by '|'
        auto split = [](string s) {
            vector<string> fields;
            size_t pos;
            while ((pos = s.find('|')) != string::npos) {
                fields.push_back(s.substr(0, pos));
                s.erase(0, pos + 1);
            }
            fields.push_back(s);
            return fields;
        };

        if (currentSection == "MEMBERS") {
            auto fields = split(line);
            if (fields.size() >= 10) {
                try {
                    int  id       = stoi(fields[0]);
                    int  age      = stoi(fields[2]);
                    bool isActive = (fields[9] == "Active");
                    Member m(id, fields[1], age, fields[3], fields[4],
                             fields[5], fields[6], fields[7], fields[8]);
                    m.setStatus(isActive);
                    members.push_back(m);
                } catch (const exception& e) {
                    cout << "Skipping invalid member line: " << e.what() << endl;
                }
            }
        }
        else if (currentSection == "TRAINERS") {
            auto fields = split(line);
            if (fields.size() >= 5) {
                try {
                    int    id     = stoi(fields[0]);
                    double salary = stod(fields[4]);
                    Trainer t(id, fields[1], fields[2], fields[3], salary, 0.0);
                    trainers.push_back(t);
                } catch (const exception& e) {
                    cout << "Skipping invalid trainer line: " << e.what() << endl;
                }
            }
        }
        else if (currentSection == "PAYMENTS") {
            auto fields = split(line);
            if (fields.size() >= 8) {
                try {
                    double amount   = stod(fields[2]);
                    double discount = stod(fields[6]);
                    double penalty  = stod(fields[7]);

                    PaymentMethod method = PaymentMethod::Cash;
                    if      (fields[4] == "Credit Card")   method = PaymentMethod::CreditCard;
                    else if (fields[4] == "Debit Card")    method = PaymentMethod::DebitCard;
                    else if (fields[4] == "Bank Transfer") method = PaymentMethod::BankTransfer;
                    else if (fields[4] == "Online")        method = PaymentMethod::Online;

                    PaymentStatus status = PaymentStatus::Pending;
                    if      (fields[5] == "Completed") status = PaymentStatus::Completed;
                    else if (fields[5] == "Failed")    status = PaymentStatus::Failed;
                    else if (fields[5] == "Refunded")  status = PaymentStatus::Refunded;

                    Payment p(fields[1], amount, fields[3], method, status, discount, penalty);
                    payments.push_back(p);
                } catch (const exception& e) {
                    cout << "Skipping invalid payment line: " << e.what() << endl;
                }
            }
        }
        else if (currentSection == "ATTENDANCE") {
            auto fields = split(line);
            if (fields.size() >= 4) {
                AttendanceRecord record(fields[0], fields[1], fields[2], fields[3]);
                attendanceRecords.push_back(record);
            }
        }
        else if (currentSection == "EXERCISES") {
            auto fields = split(line);
            if (fields.size() >= 4) {
                try {
                    Exercise ex(fields[0], stoi(fields[1]), stoi(fields[2]), stoi(fields[3]));
                    exercises.push_back(ex);
                } catch (const exception& e) {
                    cout << "Skipping invalid exercise line: " << e.what() << endl;
                }
            }
        }
        else if (currentSection == "WORKOUT_PROGRAMS") {
            if (line[0] == ' ') {
                auto fields = split(line.substr(2));
                if (fields.size() >= 4 && !workoutPrograms.empty()) {
                    try {
                        Exercise ex(fields[0], stoi(fields[1]), stoi(fields[2]), stoi(fields[3]));
                        workoutPrograms.back().addExercise(ex);
                    } catch (const exception& e) {
                        cout << "Skipping invalid exercise in program: " << e.what() << endl;
                    }
                }
            } else {
                auto fields = split(line);
                if (fields.size() >= 6) {
                    try {
                        WorkoutProgram program(stoi(fields[0]), fields[1], fields[2], fields[3], fields[4]);
                        workoutPrograms.push_back(program);
                    } catch (const exception& e) {
                        cout << "Skipping invalid program line: " << e.what() << endl;
                    }
                }
            }
        }
    }

    file.close();
    cout << "Data loaded successfully!\n";
    cout << "  - Members: "          << members.size()          << endl;
    cout << "  - Trainers: "         << trainers.size()         << endl;
    cout << "  - Payments: "         << payments.size()         << endl;
    cout << "  - Attendance Records: "<< attendanceRecords.size()<< endl;
    cout << "  - Exercises: "        << exercises.size()        << endl;
    cout << "  - Workout Programs: " << workoutPrograms.size()  << endl << endl;
}

void GymController::displayFormattedReport() const {
    cout << setw(70) << setfill('=') << "=" << endl;
    cout << setfill(' ') << "GYM MANAGEMENT SYSTEM - FORMATTED REPORT" << endl;
    cout << setw(70) << setfill('=') << "=" << endl << endl;

    cout << "MEMBERS SUMMARY:\n" << setw(70) << setfill('-') << "-" << endl;
    cout << setfill(' ');
    int activeCount = 0;
    for (const auto& m : members) if (m.getStatus()) activeCount++;
    cout << left << setw(20) << "Total Members:" << members.size()  << endl;
    cout << left << setw(20) << "Active Members:"<< activeCount     << endl << endl;

    cout << "TRAINERS SUMMARY:\n" << setw(70) << setfill('-') << "-" << endl;
    cout << setfill(' ') << left << setw(20) << "Total Trainers:" << trainers.size() << endl << endl;

    cout << "PAYMENTS SUMMARY:\n" << setw(70) << setfill('-') << "-" << endl;
    cout << setfill(' ');
    double totalRevenue = 0.0; int completedPayments = 0;
    for (const auto& p : payments) {
        if (p.getStatus() == PaymentStatus::Completed) {
            totalRevenue += p.getFinalAmount(); completedPayments++;
        }
    }
    cout << left << setw(20) << "Total Payments:"  << payments.size()    << endl;
    cout << left << setw(20) << "Completed:"        << completedPayments  << endl;
    cout << left << setw(20) << "Total Revenue: $"  << totalRevenue       << endl << endl;

    cout << "ATTENDANCE SUMMARY:\n" << setw(70) << setfill('-') << "-" << endl;
    cout << setfill(' ') << left << setw(20) << "Total Records:" << attendanceRecords.size() << endl;
    cout << setw(70) << setfill('=') << "=" << endl << endl;
}
