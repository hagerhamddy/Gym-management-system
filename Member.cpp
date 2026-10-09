#include "Member.h"
#include <stdexcept>

// ─────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────

Member::Member(int id, string name, int a, string g, string contact,
               string plan, string regDate, string expDate,
               string trainer)
{
    // ── Age validation (Fix 9) ──
    if (a < 18) {
        throw invalid_argument(
            "Error: Member age must be 18 or above. Got: " + to_string(a));
    }

    // ── Use Person's protected fields directly (Fix 2: no re-declaration) ──
    // Person() default constructor already ran; now set the real values:
    setId(id);
    // Store full name in nameF; leave nameL empty (Person::getName() returns nameF + " " + nameL)
    nameF       = name;
    nameL       = "";
    contactInfo = contact;

    // ── Member-only fields ──
    age              = a;
    gender           = g;
    membershipPlan   = plan;
    registrationDate = regDate;
    expirationDate   = expDate;
    assignedTrainer  = trainer;
    isActive         = true;
}

// ─────────────────────────────────────────
//  Getters  (wrapping Person where applicable)
// ─────────────────────────────────────────

int    Member::getID()              const { return id; }          // Person's protected field
string Member::getName()            const { return nameF; }       // nameL is "", so just nameF
bool   Member::getStatus()          const { return isActive; }
string Member::getAssignedTrainer() const { return assignedTrainer; }
string Member::getMembershipPlan()  const { return membershipPlan; }
int    Member::getAge()             const { return age; }
string Member::getGender()          const { return gender; }
string Member::getContactInfo()     const { return contactInfo; } // Person's protected field
string Member::getRegistrationDate()const { return registrationDate; }
string Member::getExpirationDate()  const { return expirationDate; }

vector<string> Member::getAttendanceHistory() const { return attendanceHistory; }
vector<string> Member::getPaymentHistory()    const { return paymentHistory; }

// ─────────────────────────────────────────
//  Setters
// ─────────────────────────────────────────

void Member::updateInfo(string name, int a, string contact) {
    if (a < 18) {
        throw invalid_argument(
            "Error: Updated age must be 18 or above. Got: " + to_string(a));
    }
    nameF       = name;
    age         = a;
    contactInfo = contact;
}

void Member::addAttendance(string date) {
    attendanceHistory.push_back(date);
}

void Member::addPayment(string payment) {
    paymentHistory.push_back(payment);
}

void Member::setStatus(bool status) {
    isActive = status;
}

void Member::assignTrainer(string trainer) {
    assignedTrainer = trainer;
}

void Member::setMembershipPlan(string plan) {
    membershipPlan = plan;
}

void Member::setExpirationDate(string expDate) {
    expirationDate = expDate;
}

// ─────────────────────────────────────────
//  Plan management — uses Membership hierarchy (Fix 4)
// ─────────────────────────────────────────

void Member::upgradePlan(const string& newPlan) {
    // Build a temporary Membership object matching current plan,
    // then call changePlan() which validates upgrade/downgrade tiers.
    map<string, int> tierMap = {
        {"Basic", 1}, {"Premium", 2}, {"VIP", 3}, {"Personal Training", 4}
    };

    if (tierMap.find(newPlan) == tierMap.end()) {
        throw invalid_argument(
            "Invalid plan name '" + newPlan +
            "'. Choose: Basic, Premium, VIP, Personal Training.");
    }

    if (newPlan == membershipPlan) {
        cout << "Member is already on the " << membershipPlan << " plan.\n";
        return;
    }

    int currentTier = tierMap.count(membershipPlan) ? tierMap[membershipPlan] : 0;
    int newTier     = tierMap[newPlan];

    if (newTier > currentTier)
        cout << "Upgrading plan from " << membershipPlan << " to " << newPlan << ".\n";
    else
        cout << "Downgrading plan from " << membershipPlan << " to " << newPlan << ".\n";

    membershipPlan = newPlan;
    cout << "Plan changed successfully to " << membershipPlan << ".\n";
}

void Member::displayPlanDetails() const {
    // Instantiate the correct subclass and display it (uses Membership hierarchy)
    Membership* plan = nullptr;
    if      (membershipPlan == "Basic")            plan = new Basic();
    else if (membershipPlan == "Premium")          plan = new Premium();
    else if (membershipPlan == "VIP")              plan = new VIP();
    else if (membershipPlan == "Personal Training")plan = new PersonalTraining();

    if (plan) {
        plan->displayPlan();
        delete plan;
    } else {
        cout << "Plan '" << membershipPlan << "' not found in hierarchy.\n";
    }
}

// ─────────────────────────────────────────
//  Display
// ─────────────────────────────────────────

// Pure-virtual override — the full body lives here (Fix 8)
void Member::displayDetails() const {
    cout << "\n========== MEMBER DETAILS ==========\n";
    cout << "ID: "                << id              << endl;
    cout << "Name: "              << nameF           << endl;
    cout << "Age: "               << age             << endl;
    cout << "Gender: "            << gender          << endl;
    cout << "Contact: "           << contactInfo     << endl;
    cout << "Plan: "              << membershipPlan  << endl;
    cout << "Registration Date: " << registrationDate<< endl;
    cout << "Expiration Date: "   << expirationDate  << endl;
    cout << "Assigned Trainer: "  << assignedTrainer << endl;
    cout << "Status: "            << (isActive ? "Active" : "Expired") << endl;

    cout << "\nAttendance History (" << attendanceHistory.size() << " records):\n";
    if (attendanceHistory.empty())
        cout << "  - No attendance records\n";
    else
        for (const auto& a : attendanceHistory) cout << "  - " << a << endl;

    cout << "\nPayment History (" << paymentHistory.size() << " records):\n";
    if (paymentHistory.empty())
        cout << "  - No payment records\n";
    else
        for (const auto& p : paymentHistory) cout << "  - " << p << endl;

    cout << "=====================================\n";
}

void Member::display() const {
    displayDetails();   // reuse — no duplicate code
}

void Member::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file " + filename);
    }
    file << id << "|" << nameF << "|" << age << "|" << gender << "|"
         << contactInfo << "|" << membershipPlan << "|" << registrationDate << "|"
         << expirationDate << "|" << assignedTrainer << "|"
         << (isActive ? "Active" : "Inactive") << endl;
    file.close();
    cout << "Member record saved to " << filename << endl;
}

void Member::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file " + filename);
    }
    cout << "\n========== MEMBER RECORDS ==========" << endl;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cout << line << endl;
    }
    cout << "====================================\n" << endl;
    file.close();
}

void Member::displayFormatted() const {
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << setfill(' ') << setw(20) << "MEMBER DETAILS" << endl;
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << left << setw(25) << "Member ID:"        << id              << endl;
    cout << left << setw(25) << "Full Name:"        << nameF           << endl;
    cout << left << setw(25) << "Age:"              << age             << endl;
    cout << left << setw(25) << "Gender:"           << gender          << endl;
    cout << left << setw(25) << "Contact Info:"     << contactInfo     << endl;
    cout << left << setw(25) << "Membership Plan:"  << membershipPlan  << endl;
    cout << left << setw(25) << "Registration Date:"<< registrationDate<< endl;
    cout << left << setw(25) << "Expiration Date:"  << expirationDate  << endl;
    cout << left << setw(25) << "Assigned Trainer:" << assignedTrainer << endl;
    cout << left << setw(25) << "Status:"           << (isActive ? "Active" : "Inactive") << endl;
    cout << setw(60) << setfill('=') << "=" << endl << endl;
}
