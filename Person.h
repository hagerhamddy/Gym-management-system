#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>   // for exception handling

using namespace std;

class Person {
protected:
    static int nextId;
    int id;
    string nameF, nameL, contactInfo;

public:
    Person();

    void setId(int id);
    void setName(string nameF, string nameL);
    void setContactInfo(string contactInfo);
    void display();

    int    getId()         const;
    string getName()       const;
    string getContactInfo() const;

    // I/O Functions
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;

    // ── Pure virtual: every derived class MUST implement this ──
    virtual void displayDetails() const = 0;

    virtual ~Person();
};

#endif // PERSON_H
