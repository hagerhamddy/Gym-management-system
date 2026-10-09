#include "AttendanceRecord.h"
using namespace std;

AttendanceRecord::AttendanceRecord() {
    MemberID = "0";
    date = "0";
    CheckInTime = "0";
    CheckOutTime = "0";
    cout << "AttendanceRecord default constructor created" << endl;
}
AttendanceRecord::AttendanceRecord(string mID, string attDate, 
                                   string inTime, string outTime) {
    MemberID = mID;
    date = attDate;
    CheckInTime = inTime;
    CheckOutTime = outTime;
    cout << "AttendanceRecord constructor created for member: " << MemberID << endl;
}
AttendanceRecord::~AttendanceRecord() {
    cout << "AttendanceRecord deleted for member: " << MemberID << endl;
}

string AttendanceRecord::getMemberID() const {
    return MemberID;
}
string AttendanceRecord::getDate() const {
    return date;
}
string AttendanceRecord::getCheckInTime() const {
    return CheckInTime;
}
string AttendanceRecord::getCheckOutTime() const {
    return CheckOutTime;
}

void AttendanceRecord::setMemberID(string mID) {
    MemberID = mID;
}
void AttendanceRecord::setDate(string attDate) {
    date = attDate;
}
void AttendanceRecord::setCheckInTime(string inTime) {
    CheckInTime = inTime;
}
void AttendanceRecord::setCheckOutTime(string outTime) {
    CheckOutTime = outTime;
}

void AttendanceRecord::displayAttendance() const {
    cout << "Member ID: " << MemberID << endl;
    cout << "Date: " << date << endl;
    cout << "Check-in Time: " << CheckInTime << endl;
    cout << "Check-out Time: " << CheckOutTime << endl << endl;
}

void AttendanceRecord::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    file << MemberID << "|" << date << "|" << CheckInTime << "|" << CheckOutTime << endl;
    file.close();
    cout << "Attendance record saved to " << filename << endl;
}

void AttendanceRecord::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    cout << "\n===== ATTENDANCE RECORDS =====" << endl;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cout << line << endl;
    }
    cout << "=============================\n" << endl;
    file.close();
}

void AttendanceRecord::displayFormatted() const {
    cout << setw(55) << setfill('-') << "-" << endl;
    cout << setfill(' ') << "ATTENDANCE RECORD" << endl;
    cout << setw(55) << setfill('-') << "-" << endl;
    cout << left << setw(25) << "Member ID:" << MemberID << endl;
    cout << left << setw(25) << "Date:" << date << endl;
    cout << left << setw(25) << "Check-in Time:" << CheckInTime << endl;
    cout << left << setw(25) << "Check-out Time:" << CheckOutTime << endl;
    cout << setw(55) << setfill('-') << "-" << endl << endl;
}