#ifndef GYM_H
#define GYM_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Membership {
private:
	int planID;
	string planName;
	int durationmonths;
	double price;
	string accessLevel;
	string services;
	double discount;
public:
	Membership(int a,
		string b,
		int c,
		double d,
		string e,
		string f,
		double g);

	int getplanID() const;
	string getplanName() const;
	int getdurationmonths() const;
	double getprice() const;
	string getaccessLevel() const;
	string getservices() const;
	void displayPlan();
	double getFinalPrice();
	void changePlan(string newPlan);
	void calculateExpiration(int startMonth, int startYear);
};
class Basic : public Membership {
public:
	Basic() : Membership(1, "Basic", 1, 500,
		"Gym only",
		"machines",
		0) {
	}
}; 
class Premium : public Membership {
public:
	Premium() : Membership(2, "Premium", 1, 800,
		"Gym + Classes",
		"machines + cardio",
		10) {
	}
};
class VIP : public Membership {
public:
	VIP() : Membership(3, "VIP", 1, 1200,
		"Full Access",
		"all services",
		15) {
	}
};
class PersonalTraining : public Membership {
public:
    PersonalTraining() : Membership(4, "Personal Training", 1, 2000,
        "Personal Training + Gym",
        "all services",
        15) {
    }
};

#endif // GYM_H