#include <iostream>
#include <sstream>
#include "Store.h"
#include "Product.h"
#include "Customer.h"

using namespace std;

int Store::counter = 0; // defines and initializes

Store::Store() : numProducts(0), numCustomers(0) {
	setName(""); //initializes store name
}

Store::Store(const char name[]) : 
	numProducts(0), numCustomers(0) {
	setName(name);
}

const char * Store::getName() {
	return name;
}

void Store::setName(const char storeName[]) {
	if (strlen(storeName) > 0) {
		strcpy(this->name, storeName);
	}
	else {
		counter++;
		ostringstream oss;
		oss << "Store " << counter;
		strcpy(this->name, oss.str().c_str());
	}
}

bool Store::addProduct(int productID, const char productName[]) {
	for (int i = 0; i < numProducts; i++) {
		if (productID == products[i]->getID() || numProducts == 100) {
			return false;
		}
	}
	Product *prod = new Product(productID, productName); //creates new product
	products[numProducts] = prod;
	numProducts++;
	return true;
}

Product * Store::getProduct(int customerID) {
	for (int i = 0; i < numProducts; i++) {
		if (products[i]->getID() == customerID) {
			return products[i];
		}
	}
	return nullptr;
}

bool Store::addCustomer(int customerID, const char customerName[], bool credit) {
	for (int i = 0; i < numCustomers; i++) {
		if (customerID == customers[i]->getID() || numCustomers == 100) {
			return false;
		}
	}
	Customer *cust = new Customer(customerID, customerName, credit); //creates new customer
	customers[numCustomers] = cust;
	numCustomers++;
	return true;
}

Customer * Store::getCustomer(int productID)
{
	for (int i = 0; i < numCustomers; i++) {
		if (customers[i]->getID() == productID) {
			return customers[i];
		}
	}
	return nullptr;
}

bool Store::takeShipment(int productID, int quantity, double cost) {
	if (quantity > 0 && cost > 0) { // checks if cost and quantity are positive
		for (int i = 0; i < numProducts; i++) {
			if (productID == products[i]->getID()) {
				products[i]->addShipment(quantity, cost);
				return true;
			}
		}
	}
	return false;

}

bool Store::sellProduct(int customerID, int productID, int quantity) {
	if (quantity > 0) {
		for (int i = 0; i < numCustomers; i++) {
			if (customers[i]->getID() == customerID) {
				for (int j = 0; j < numProducts; j++) {
					if (productID == products[j]->getID()){
						if (customers[i]->processPurchase(products[j]->getPrice()*quantity, *products[j]) && products[j]->reduceInventory(quantity)) {
							//checks if purchase works
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Store::takePayment(int customerID, double amount) {
	if (amount > 0) { //checks if amount is positive
		for (int i = 0; i < numCustomers; i++) {
			if (customers[i]->getID() == customerID) {
				customers[i]->processPayment(amount);
				return true;
			}
		}
	}
	return false;
}

void Store::outputProducts(std::ostream & os) {
	for (int i = 0; i < numProducts; i++) {
		os << *products[i] << endl;
	}
}

void Store::outputCustomers(std::ostream & os) {
	for (int i = 0; i < numCustomers; i++) {
		os << *customers[i] << endl;
	}
}
