#include "./Trainer.h"
#include <iostream>
#include "Person.h"

// Default constructor
Trainer::Trainer() : Person(), specialty(""), salary(0.0), commissionRate(0.0) {}

// Constructor with parameters
Trainer::Trainer(int id, std::string name, std::string contact, std::string spec, double sal, double comm)
 : Person(), specialty(spec), salary(sal), commissionRate(comm) {
    setId(id);
    setName(name, "");  // Person stores full name in nameF
    setContactInfo(contact);
}
void Trainer::setSpecialty(const std::string &spec)
{
    specialty = spec;
}

std::string Trainer::getSpecialty() const
{
    return specialty;
}

void Trainer::setSalary(double sal)
{
    if (sal >= 0)
        salary = sal;
}

double Trainer::getSalary() const
{
    return salary;
}

void Trainer::addMember(int memberID)
{
    // Aggregation: Trainer holds a list of assigned members/
    assignedMemberIDs.push_back(memberID);
}

const std::vector<int> &Trainer::getAssignedMembers() const
{
    return assignedMemberIDs;
}

void Trainer::displayDetails() const {
    // Using inherited getters from Person class
    std::cout << "Trainer ID: " << getId() << "\n"
              << "Name: " << getName() << "\n"
              << "Contact: " << getContactInfo() << "\n"
              << "Specialty: " << specialty << "\n"
              << "Salary: $" << salary << "\n"
              << "Members Assigned: " << assignedMemberIDs.size() << std::endl;
}

void Trainer::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return;
    }
    file << getId() << "|" << getName() << "|" << getContactInfo() << "|"
         << specialty << "|" << salary << "|" << assignedMemberIDs.size() << std::endl;
    file.close();
    std::cout << "Trainer record saved to " << filename << std::endl;
}

void Trainer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return;
    }
    std::cout << "\n====== TRAINER RECORDS ======" << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::cout << line << std::endl;
    }
    std::cout << "=============================\n" << std::endl;
    file.close();
}

void Trainer::displayFormatted() const {
    std::cout << std::setw(55) << std::setfill('=') << "=" << std::endl;
    std::cout << std::setfill(' ') << "TRAINER DETAILS" << std::endl;
    std::cout << std::setw(55) << std::setfill('=') << "=" << std::endl;
    std::cout << std::left << std::setw(25) << "ID:" << getId() << std::endl;
    std::cout << std::left << std::setw(25) << "Name:" << getName() << std::endl;
    std::cout << std::left << std::setw(25) << "Contact:" << getContactInfo() << std::endl;
    std::cout << std::left << std::setw(25) << "Specialty:" << specialty << std::endl;
    std::cout << std::left << std::setw(25) << "Salary: $" << salary << std::endl;
    std::cout << std::left << std::setw(25) << "Members Assigned:" << assignedMemberIDs.size() << std::endl;
    std::cout << std::setw(55) << std::setfill('=') << "=" << std::endl << std::endl;
}

Trainer::~Trainer() {}