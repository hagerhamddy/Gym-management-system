#ifndef TRAINER_H
#define TRAINER_H

#include "Person.h" // TODO: Include the header file for the Person class, which Trainer will inherit from.
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

// trainer is derived from person class,
class Trainer : public Person 
{
private:
    // Encapsulation:
    std::string specialty; // e.g., Cardio, Strength, CrossFit,
    double salary;
    double commissionRate;
    std::vector<int> assignedMemberIDs; // List of assigned member IDs,

public:
    // Constructor Overloading,
    Trainer();
    Trainer(int id, std::string name, std::string contact, std::string spec, double sal, double comm);

    // Getters and Setters (Const correctness(
    void setSpecialty(const std::string &spec);
    std::string getSpecialty() const;

    void setSalary(double sal);
    double getSalary() const;

    // Trainer specific functionality
    void addMember(int memberID);                       
    const std::vector<int> &getAssignedMembers() const; 

    // Polymorphism if a virtual function exists in the person class,
    void displayDetails() const override;

    // I/O Functions
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;

    // Destructor
    virtual ~Trainer();
};

#endif