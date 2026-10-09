#ifndef PAYMENT_H
#define PAYMENT_H
 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
 
// ─────────────────────────────────────────
//  Enums
// ─────────────────────────────────────────
 
enum class PaymentMethod {
    Cash, CreditCard, DebitCard, BankTransfer, Online
};
 
enum class PaymentStatus {
    Pending, Completed, Failed, Refunded
};
 
// ─────────────────────────────────────────
//  Enum Helper Declarations
// ─────────────────────────────────────────
 
string methodToString(PaymentMethod m);
string statusToString(PaymentStatus s);
 
// ─────────────────────────────────────────
//  Payment Class
// ─────────────────────────────────────────
 
class Payment {
private:
    string        paymentID;
    string        memberID;
    double        amount;
    string        date;
    PaymentMethod method;
    PaymentStatus status;
    double        discount;
    double        penalty;
    string        notes;
 
    static int idCounter;
 
public:
 
    // ─ ID Generator ─
    static string generatePaymentID();
 
    // ─ Constructor ─
    Payment(string memberID, double amount, string date,
            PaymentMethod method,
            PaymentStatus status  = PaymentStatus::Pending,
            double discount       = 0.0,
            double penalty        = 0.0,
            string notes          = "");
 
    // ─ Getters ─
    string        getPaymentID() const;
    string        getMemberID()  const;
    double        getAmount()    const;
    string        getDate()      const;
    PaymentMethod getMethod()    const;
    PaymentStatus getStatus()    const;
    double        getDiscount()  const;
    double        getPenalty()   const;
    string        getNotes()     const;
    string        getMethodStr() const;
    string        getStatusStr() const;
    double        getFinalAmount() const;
 
    // ─ Setters ─
    void setAmount(double a);
    void setDiscount(double d);
    void setPenalty(double p);
    void setStatus(PaymentStatus s);
    void setNotes(string n);
 
    // ─ Display ─
    void displayReceipt() const;
    
    // ─ I/O Functions ─
    void saveToFile(const string& filename) const;
    static void loadFromFile(const string& filename);
    void displayFormatted() const;
 
    // ─ isUnpaid ─
    bool isUnpaid() const;
}; 
 
// ─────────────────────────────────────────
//  Utility Function Declaration
// ─────────────────────────────────────────
 
void trackUnpaidBalances(const vector<Payment>& payments);
 
#endif // PAYMENT_H