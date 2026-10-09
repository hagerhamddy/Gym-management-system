#ifndef MEMBER_H
#define MEMBER_H

#include "Person.h"
#include "gym.h"          // for Membership hierarchy
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Member : public Person {
private:
    // ── Fields that ONLY Member needs (Person already owns id, nameF/nameL, contactInfo) ──
    int    age;
    string gender;
    string membershipPlan;      // plan name string, kept for file I/O convenience
    string registrationDate;
    string expirationDate;
    string assignedTrainer;
    vector<string> attendanceHistory;
    vector<string> paymentHistory;
    bool   isActive;

public:
    // Constructor — calls Person() implicitly then sets member-specific fields
    Member(int id, string name, int age, string gender, string contact,
           string plan, string regDate, string expDate,
           string trainer = "None");

    // ── Getters ──
    // NOTE: getID(), getName(), getContactInfo() come from Person — no need to redeclare
    int    getID()         const;   // wraps Person::getId()
    string getName()       const;   // wraps Person::getName()
    bool   getStatus()     const;
    string getAssignedTrainer()  const;
    string getMembershipPlan()   const;
    int    getAge()              const;
    string getGender()           const;
    string getContactInfo()      const;   // wraps Person::getContactInfo()
    string getRegistrationDate() const;
    string getExpirationDate()   const;
    vector<string> getAttendanceHistory() const;
    vector<string> getPaymentHistory()    const;

    // ── Setters / updaters ──
    void updateInfo(string name, int age, string contact);
    void addAttendance(string date);
    void addPayment(string payment);
    void setStatus(bool status);
    void assignTrainer(string trainer);
    void setMembershipPlan(string plan);
    void setExpirationDate(string expDate);

    // ── Plan management (uses Membership hierarchy) ──
    void upgradePlan(const string& newPlan);   // calls Membership::changePlan logic
    void displayPlanDetails() const;           // shows current plan info via hierarchy

    // ── Display ──
    void display()        const;
    void displayDetails() const override;  // pure-virtual override — body lives here

    // ── I/O ──
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;
};

#endif // MEMBER_H
