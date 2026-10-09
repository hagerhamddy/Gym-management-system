#include "Person.h"
#include <iostream>

int Person::nextId = 1;

Person::Person() {
    id = nextId++;
    nameF = "Unknown";
    nameL = "Unknown";
    contactInfo = "None";
}

void Person::setId(int id) {
    if (id >= 0) {
        this->id = id;
    } else {
        throw invalid_argument("Error: ID cannot be negative.");
    }
}

void Person::setName(string nameF, string nameL) {
    this->nameF = nameF;
    this->nameL = nameL;
}

void Person::setContactInfo(string contactInfo) {
    this->contactInfo = contactInfo;
}

int Person::getId() const {
    return id;
}

string Person::getName() const {
    return nameF + " " + nameL;
}

string Person::getContactInfo() const {
    return contactInfo;
}

void Person::display() {
    cout << "ID: " << id << " | Name: " << nameF << " " << nameL
         << " | Contact: " << contactInfo << endl;
    cout << "___________________________________" << endl;
}

void Person::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file " + filename);
    }
    file << id << "|" << nameF << "|" << nameL << "|" << contactInfo << endl;
    file.close();
    cout << "Person record saved to " << filename << endl;
}

void Person::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file " + filename);
    }
    cout << "\n======== PERSON RECORDS ========" << endl;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cout << line << endl;
    }
    cout << "================================\n" << endl;
    file.close();
}

void Person::displayFormatted() const {
    cout << setw(50) << setfill('-') << "-" << endl;
    cout << setfill(' ') << "PERSON RECORD" << endl;
    cout << setw(50) << setfill('-') << "-" << endl;
    cout << left << setw(20) << "ID:"           << id          << endl;
    cout << left << setw(20) << "First Name:"   << nameF       << endl;
    cout << left << setw(20) << "Last Name:"    << nameL       << endl;
    cout << left << setw(20) << "Contact Info:" << contactInfo << endl;
    cout << setw(50) << setfill('-') << "-" << endl << endl;
}

// NOTE: displayDetails() removed — it is pure virtual (= 0 in header).
// Each derived class (Member, Trainer) provides its own body.

Person::~Person() {}
