#include "WorkoutProgram.h"

WorkoutProgram::WorkoutProgram(int id, string n, string goal, string dur, string trainer)
    : programID(id), name(n), targetGoal(goal), duration(dur), assignedTrainer(trainer) {}

int WorkoutProgram::getProgramID() const {
    return programID;
}

string WorkoutProgram::getName() const {
    return name;
}

string WorkoutProgram::getTargetGoal() const {
    return targetGoal;
}

string WorkoutProgram::getDuration() const {
    return duration;
}

string WorkoutProgram::getAssignedTrainer() const {
    return assignedTrainer;
}

void WorkoutProgram::addExercise(const Exercise& exercise) {
    exerciseList.push_back(exercise);
    cout << "Exercise added: " << exercise.getExerciseName() << endl;
}

void WorkoutProgram::removeExercise(int exerciseIndex) {
    if (exerciseIndex >= 0 && exerciseIndex < exerciseList.size()) {
        cout << "Removed: " << exerciseList[exerciseIndex].getExerciseName() << endl;
        exerciseList.erase(exerciseList.begin() + exerciseIndex);
    } else {
        cout << "Invalid exercise index\n";
    }
}

void WorkoutProgram::displayExercises() const {
    if (exerciseList.empty()) {
        cout << "No exercises in this program\n";
        return;
    }
    for (const auto& ex : exerciseList) {
        ex.displayExercise();
    }
}

const vector<Exercise>& WorkoutProgram::getExerciseList() const {
    return exerciseList;
}

void WorkoutProgram::displayProgram() const {
    cout << "\nProgram ID: " << programID << endl;
    cout << "Name: " << name << endl;
    cout << "Target Goal: " << targetGoal << endl;
    cout << "Duration: " << duration << endl;
    cout << "Assigned Trainer: " << assignedTrainer << endl;
    cout << "Exercises:\n";
    displayExercises();
}

void WorkoutProgram::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    file << programID << "|" << name << "|" << targetGoal << "|"
         << duration << "|" << assignedTrainer << "|" << exerciseList.size() << endl;
    file.close();
    cout << "WorkoutProgram record saved to " << filename << endl;
}

void WorkoutProgram::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    cout << "\n======= WORKOUT PROGRAM RECORDS ========" << endl;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cout << line << endl;
    }
    cout << "=========================================\n" << endl;
    file.close();
}

void WorkoutProgram::displayFormatted() const {
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << setfill(' ') << "WORKOUT PROGRAM DETAILS" << endl;
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << left << setw(30) << "Program ID:" << programID << endl;
    cout << left << setw(30) << "Name:" << name << endl;
    cout << left << setw(30) << "Target Goal:" << targetGoal << endl;
    cout << left << setw(30) << "Duration:" << duration << endl;
    cout << left << setw(30) << "Assigned Trainer:" << assignedTrainer << endl;
    cout << left << setw(30) << "Number of Exercises:" << exerciseList.size() << endl;
    cout << setw(60) << setfill('=') << "=" << endl << endl;
}
