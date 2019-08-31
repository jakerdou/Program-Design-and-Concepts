#include <iostream>
#include <sstream>
#include "Customer.h"
#include "Product.h"
#include <string.h>
using namespace std;

int Customer::counter = 0; // defines and initializes

//constructor
Customer::Customer(int customerID, const char name[], bool credit) :
	id(customerID), balance(0), numPurchased(0) {
	setName(name);
	setCredit(credit);
}

int Customer::getID() const { return id; }

const char * Customer::getName() const { return name; }

void Customer::setName(char const customerName[]) {
	if (strlen(customerName) > 0) {
		strcpy(this->name, customerName);
	}
	else {
		counter++;
		ostringstream oss;
		oss << "Customer " << counter;
		strcpy(this->name, oss.str().c_str());
	}
}

bool Customer::getCredit() const {
	return credit;
}

void Customer::setCredit(bool hasCredit) {
	credit = hasCredit;
}

double Customer::getBalance() const {
	return balance;
}

bool Customer::processPayment(double amount) {
	if (amount >= 0) { //checks if amount is positive
		balance = balance + amount;
		return true;
	}
	else {
		return false;
	}
}

bool Customer::processPurchase(double amount, Product product) {
	if (!credit && (balance - amount < 0)) { //if no credit and purchase makes balance negative, purchase doesn't happen
		return false;
	}
	else {
		for (int i = 0; i < numPurchased; i++) { //if product has been purchased before, doesnt add to recently purchased list
			if (strcmp(product.getName(),productsPurchased[i])==0) {
				return true;
			}
		}
		balance = balance - amount;
		for (int i = numPurchased - 1; i >= 0; i--) {
			if (i<4) {
				strcpy(productsPurchased[i+1], productsPurchased[i]);
			}	
		}
		strcpy(productsPurchased[0], product.getName());
		numPurchased++;
	}
	return true;
}


void Customer::outputRecentPurchases(std::ostream & os) const {
	os << "Products Purchased --" << endl;

	if (numPurchased == 0) {
	}
	else {
		for (int i = 0; i < numPurchased; i++) {
			if (i < 5) {
				os << productsPurchased[i] << endl;
			}
		}
	}
}

std::ostream & operator<<(std::ostream & os, const Customer & customer) {
	os << "Customer Name: " << customer.getName() << endl;
	os << "Customer ID: " << customer.getID() << endl;
	os << "Has Credit: ";
	if (customer.getCredit()) { //checks credit 
		os << "true" << endl;
	}
	else {
		os << "false" << endl;
	}
	os << "Balance: " << customer.getBalance() << endl;
	customer.outputRecentPurchases(os);
	return os;
}
