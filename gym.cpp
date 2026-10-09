#include "gym.h"

Membership::Membership(int a,
                       string b,
                       int c,
                       double d,
                       string e,
                       string f,
                       double g)
{
    planID = a;
    planName = b;
    durationmonths = c;
    price = d;
    accessLevel = e;
    services = f;
    discount = g;
}
int Membership::getplanID() const {
    return planID;
}
string Membership::getplanName() const {
    return planName;
}
int Membership::getdurationmonths() const {
    return durationmonths;
}
double Membership::getprice() const {
    return price;
}
string Membership::getaccessLevel() const {
    return accessLevel;
}
string Membership::getservices()const {
    return services;
}
void Membership::displayPlan() {
    cout << "Plan ID: " << planID << endl;
    cout << "Plan Name: " << planName << endl;
    cout << "Duration: " << durationmonths << " months" << endl;
    cout << "Price: " << price << endl;
    cout << "Discount: " << discount << "%" << endl;
    cout << "Final Price: " << getFinalPrice() << endl;
    cout << "Access Level: " << accessLevel << endl;
    cout << "Services: " << services << endl;
}
double Membership::getFinalPrice() {
    return price - (price * discount / 100);
}
void Membership::changePlan(string newPlan) {
    if (newPlan == planName) {
        cout << "Invalid change: already on " << planName << " plan.\n";
        return;
    }
    // Tier order: Basic(1) < Premium(2) < VIP(3) < PersonalTraining(4)
    map<string, int> tierMap = {
        {"Basic", 1}, {"Premium", 2}, {"VIP", 3}, {"Personal Training", 4}
    };
    if (tierMap.find(newPlan) == tierMap.end()) {
        cout << "Invalid plan name. Choose: Basic, Premium, VIP, Personal Training.\n";
        return;
    }
    int currentTier = tierMap.count(planName) ? tierMap[planName] : 0;
    int newTier = tierMap[newPlan];
    if (newTier > currentTier)
        cout << "Upgrading plan from " << planName << " to " << newPlan << ".\n";
    else
        cout << "Downgrading plan from " << planName << " to " << newPlan << ".\n";
    planName = newPlan;
    cout << "Plan changed successfully to " << planName << ".\n";
}
void Membership::calculateExpiration(int startMonth, int startYear) {
    int endMonth = startMonth + durationmonths;
    int endYear = startYear;

    while (endMonth > 12) {
        endMonth -= 12;
        endYear++;
    }

    cout << "Expiration Date: "
        << endMonth << "/" << endYear << endl;
}


