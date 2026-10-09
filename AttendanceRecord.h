#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class AttendanceRecord {
private:
    string MemberID;
    string date;
    string CheckInTime;
    string CheckOutTime;

public:
    // 2 Constructors + 1 Destructor
    AttendanceRecord();
    AttendanceRecord(string mID, string attDate, string inTime, string outTime);
    ~AttendanceRecord();

    // Getters
    string getMemberID() const;
    string getDate() const;
    string getCheckInTime() const;
    string getCheckOutTime() const;

    // Setters
    void setMemberID(string mID);
    void setDate(string attDate);
    void setCheckInTime(string inTime);
    void setCheckOutTime(string outTime);

    void displayAttendance() const;
    
    // I/O Functions
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;
};

#endif
