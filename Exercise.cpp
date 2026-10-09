#include "Exercise.h"

Exercise::Exercise(string name, int s, int r, int restT)
    : exerciseName(name), sets(s), reps(r), restTime(restT) {}

string Exercise::getExerciseName() const {
    return exerciseName;
}

int Exercise::getSets() const {
    return sets;
}

int Exercise::getReps() const {
    return reps;
}

int Exercise::getRestTime() const {
    return restTime;
}

void Exercise::setExerciseName(string name) {
    exerciseName = name;
}

void Exercise::setSets(int s) {
    if (s > 0) {
        sets = s;
    } else {
        cout << "Error: Sets must be positive." << endl;
    }
}

void Exercise::setReps(int r) {
    if (r > 0) {
        reps = r;
    } else {
        cout << "Error: Reps must be positive." << endl;
    }
}

void Exercise::setRestTime(int restT) {
    if (restT >= 0) {
        restTime = restT;
    } else {
        cout << "Error: Rest time cannot be negative." << endl;
    }
}

void Exercise::displayExercise() const {
    cout << "Exercise: " << exerciseName << " | "
         << "Sets: " << sets << " | "
         << "Reps: " << reps << " | "
         << "Rest: " << restTime << "s" << endl;
}

void Exercise::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    file << exerciseName << "|" << sets << "|" << reps << "|" << restTime << endl;
    file.close();
    cout << "Exercise record saved to " << filename << endl;
}

void Exercise::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    cout << "\n======== EXERCISE RECORDS ========" << endl;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cout << line << endl;
    }
    cout << "===================================\n" << endl;
    file.close();
}

void Exercise::displayFormatted() const {
    cout << setw(50) << setfill('-') << "-" << endl;
    cout << setfill(' ') << "EXERCISE DETAILS" << endl;
    cout << setw(50) << setfill('-') << "-" << endl;
    cout << left << setw(25) << "Exercise Name:" << exerciseName << endl;
    cout << left << setw(25) << "Sets:" << sets << endl;
    cout << left << setw(25) << "Reps:" << reps << endl;
    cout << left << setw(25) << "Rest Time (seconds):" << restTime << endl;
    cout << setw(50) << setfill('-') << "-" << endl << endl;
}
