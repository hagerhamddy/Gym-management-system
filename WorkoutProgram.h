#ifndef WORKOUTPROGRAM_H
#define WORKOUTPROGRAM_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "Exercise.h"
using namespace std;

class WorkoutProgram {
private:
    int programID;
    string name;
    string targetGoal;
    vector<Exercise> exerciseList;
    string duration;
    string assignedTrainer;

public:
    // Constructor
    WorkoutProgram(int id, string n, string goal, string dur, string trainer);

    // Getters
    int getProgramID() const;
    string getName() const;
    string getTargetGoal() const;
    string getDuration() const;
    string getAssignedTrainer() const;
    
    // Exercise Management
    void addExercise(const Exercise& exercise);
    void removeExercise(int exerciseIndex);
    void displayExercises() const;
    const vector<Exercise>& getExerciseList() const;

    // Display
    void displayProgram() const;
    
    // I/O Functions
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;
};

#endif // WORKOUTPROGRAM_H
