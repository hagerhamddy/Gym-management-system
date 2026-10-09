#include "Payment.h"
 
// ─────────────────────────────────────────
//  Static Member Initialization
// ─────────────────────────────────────────
 
int Payment::idCounter = 0;
 
// ─────────────────────────────────────────
//  Enum Helper Definitions
// ─────────────────────────────────────────
 
string methodToString(PaymentMethod m) {
    switch (m) {
        case PaymentMethod::Cash:         return "Cash";
        case PaymentMethod::CreditCard:   return "Credit Card";
        case PaymentMethod::DebitCard:    return "Debit Card";
        case PaymentMethod::BankTransfer: return "Bank Transfer";
        case PaymentMethod::Online:       return "Online";
        default:                          return "Unknown";
    }
}
 
string statusToString(PaymentStatus s) {
    switch (s) {
        case PaymentStatus::Pending:   return "Pending";
        case PaymentStatus::Completed: return "Completed";
        case PaymentStatus::Failed:    return "Failed";
        case PaymentStatus::Refunded:  return "Refunded";
        default:                       return "Unknown";
    }
}
 
// ─────────────────────────────────────────
//  ID Generator
// ─────────────────────────────────────────
 
string Payment::generatePaymentID() {
    ++idCounter;
 
    string num = to_string(idCounter);
    while (num.length() < 4)
        num = "0" + num;
 
    return "PAY-" + num;
}
// ─────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────
 
Payment::Payment(string memberID, double amount, string date,
                 PaymentMethod method, PaymentStatus status,
                 double discount, double penalty, string notes) {
 
    this->paymentID = generatePaymentID();
    this->memberID  = memberID;
    this->date      = date;
    this->method    = method;
    this->status    = status;
    this->notes     = notes;
    this->discount  = 0.0;
    this->penalty   = 0.0;
    this->amount    = 0.0;
 
    setAmount(amount);
    setDiscount(discount);
    setPenalty(penalty);
}
 
// ─────────────────────────────────────────
//  Getters
// ─────────────────────────────────────────
 
string        Payment::getPaymentID() const { return paymentID;              }
string        Payment::getMemberID()  const { return memberID;               }
double        Payment::getAmount()    const { return amount;                 }
string        Payment::getDate()      const { return date;                   }
PaymentMethod Payment::getMethod()    const { return method;                 }
PaymentStatus Payment::getStatus()    const { return status;                 }
double        Payment::getDiscount()  const { return discount;               }
double        Payment::getPenalty()   const { return penalty;                }
string        Payment::getNotes()     const { return notes;                  }
string        Payment::getMethodStr() const { return methodToString(method); }
string        Payment::getStatusStr() const { return statusToString(status); }
 
double Payment::getFinalAmount() const {
    return amount - discount + penalty;
}
 
// ─────────────────────────────────────────
//  Setters
// ─────────────────────────────────────────
 
void Payment::setAmount(double a) {
    if (a < 0) {
        cout << "Error: Amount cannot be negative.\n";
        return;
    }
    amount = a;
}
void Payment::setDiscount(double d) {
    if (d < 0) {
        cout << "Error: Discount cannot be negative.\n";
        return;
    }
    if (d > amount) {
        cout << "Error: Discount cannot exceed the amount.\n";
        return;
    }
    discount = d;
}
 
void Payment::setPenalty(double p) {
    if (p < 0) {
        cout << "Error: Penalty cannot be negative.\n";
        return;
    }
    penalty = p;
}
 
void Payment::setStatus(PaymentStatus s) { status = s; }
void Payment::setNotes(string n)         { notes  = n; }
 
// ─────────────────────────────────────────
//  Display Receipt
// ─────────────────────────────────────────
 
void Payment::displayReceipt() const {
    cout << "\n  ==============================\n";
    cout <<   "         PAYMENT RECEIPT        \n";
    cout <<   "  ==============================\n";
    cout << "  Payment ID : " << paymentID              << "\n";
    cout << "  Member  ID : " << memberID               << "\n";
    cout << "  Date       : " << date                   << "\n";
    cout << "  Method     : " << methodToString(method) << "\n";
    cout << "  Status     : " << statusToString(status) << "\n";
    cout << "  ------------------------------\n";
    cout << "  Base Amount: $" << amount                << "\n";
    cout << "  Discount   : $" << discount              << "\n";
    cout << "  Penalty    : $" << penalty               << "\n";
    cout << "  TOTAL      : $" << getFinalAmount()      << "\n";
    if (!notes.empty())
    cout << "  Notes      :  " << notes                 << "\n";
    cout << "  ==============================\n\n";
}
 
// ─────────────────────────────────────────
//  isUnpaid
// ─────────────────────────────────────────
 
bool Payment::isUnpaid() const {
    return status == PaymentStatus::Pending ||
           status == PaymentStatus::Failed;
}

// ─────────────────────────────────────────
//  I/O Functions
// ─────────────────────────────────────────

void Payment::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    file << paymentID << "|" << memberID << "|" << amount << "|" << date << "|"
         << methodToString(method) << "|" << statusToString(status) << "|"
         << discount << "|" << penalty << endl;
    file.close();
    cout << "Payment record saved to " << filename << endl;
}

void Payment::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    cout << "\n========== PAYMENT RECORDS ==========" << endl;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cout << line << endl;
    }
    cout << "====================================\n" << endl;
    file.close();
}

void Payment::displayFormatted() const {
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << setfill(' ') << "PAYMENT DETAILS" << endl;
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << left << setw(25) << "Payment ID:" << paymentID << endl;
    cout << left << setw(25) << "Member ID:" << memberID << endl;
    cout << left << setw(25) << "Amount: $" << amount << endl;
    cout << left << setw(25) << "Date:" << date << endl;
    cout << left << setw(25) << "Method:" << methodToString(method) << endl;
    cout << left << setw(25) << "Status:" << statusToString(status) << endl;
    cout << left << setw(25) << "Discount: $" << discount << endl;
    cout << left << setw(25) << "Penalty: $" << penalty << endl;
    cout << left << setw(25) << "Final Amount: $" << getFinalAmount() << endl;
    cout << setw(60) << setfill('=') << "=" << endl << endl;
}
 
// ─────────────────────────────────────────
//  Track Unpaid Balances (Utility Function)
// ─────────────────────────────────────────
 
void trackUnpaidBalances(const vector<Payment>& payments) {
    cout << "\n  ==============================\n";
    cout <<   "       UNPAID BALANCES          \n";
    cout <<   "  ==============================\n";
 
    double totalUnpaid = 0.0;
    int    count       = 0;
 
    for (const Payment& p : payments) {
        if (p.isUnpaid()) {
            cout << "  Payment ID : " << p.getPaymentID()   << "\n";
            cout << "  Member  ID : " << p.getMemberID()    << "\n";
            cout << "  Date       : " << p.getDate()        << "\n";
            cout << "  Status     : " << p.getStatusStr()   << "\n";
            cout << "  Balance Due: $" << p.getFinalAmount() << "\n";
            cout << "  ------------------------------\n";
 
            totalUnpaid += p.getFinalAmount();
            ++count;
        }
    }
 
    if (count == 0) {
        cout << "  No unpaid balances found.\n";
    } else {
        cout << "  Unpaid Count   : " << count        << "\n";
        cout << "  Total Unpaid   : $" << totalUnpaid << "\n";
    }
 
    cout << "  ==============================\n\n";
}
