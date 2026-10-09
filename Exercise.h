#ifndef EXERCISE_H
#define EXERCISE_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Exercise {
private:
    string exerciseName;
    int sets;
    int reps;
    int restTime;  // in seconds

public:
    // Constructor
    Exercise(string name, int s, int r, int restT);
    
    // Getters
    string getExerciseName() const;
    int getSets() const;
    int getReps() const;
    int getRestTime() const;
    
    // Setters
    void setExerciseName(string name);
    void setSets(int s);
    void setReps(int r);
    void setRestTime(int restT);
    
    // Display
    void displayExercise() const;
    
    // I/O Functions
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;
};

#endif // EXERCISE_H
