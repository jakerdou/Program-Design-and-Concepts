#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
	numNode = 0;
}

LinkedList::~LinkedList() {
	clear();
}

LinkedList::LinkedList(const LinkedList& source) {
	this->numNode = source.numNode;
	Node* node1 = source.head;
	if (node1 != nullptr) {
		Node* newNode = new Node();
		newNode->data = node1->data;
		newNode->next = node1->next;
		this->head = newNode;
		Node* node2 = this->head;
		node1 = node1->next;

		while (node1 != nullptr) {
			newNode = new Node;
			newNode->data = node1->data;
			newNode->next = node1->next;
			node2->next = newNode;
			node2 = node2->next;
			node1 = node1->next;
		}
	}	
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	LinkedList* Copy = new LinkedList;
	Copy->head = source.head;
	this->numNode = source.numNode;
	Node* node1 = source.head;
	if (node1 != nullptr) {
		Node* newNode = new Node();
		newNode->data = node1->data;
		newNode->next = node1->next;
		this->head = newNode;
		Node* node2 = this->head;
		node1 = node1->next;

		while (node1 != nullptr) {
			newNode = new Node;
			newNode->data = node1->data;
			newNode->next = node1->next;
			node2->next = newNode;
			node2 = node2->next;
			node1 = node1->next;
		}
	}
	return *Copy;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	bool errVal = false;
	if (year < 1800 || year > 2018) {
		errVal = true;
		cout << "Error: Invalid year " << year << endl;
	}
	if (month < 1 || month > 12) {
		errVal = true;
		cout << "Error: Invalid month " << month << endl;
	}
	if (temperature < -99 && temperature > -100) {
		errVal = true;
	}
	if ((temperature < -50.0 || temperature > 50.0) && !(temperature < -99 && temperature > -100)) {
		errVal = true;
		cout << "Error: Invalid temperature " << temperature << endl;;
	}
	if (errVal == false) {
		Node* newNode = new Node(location, year, month, temperature);
		numNode++;
		if (numNode == 1) {
			head = newNode;
			tail = newNode;
		}
		else {
			Node* check = head;
			Node* prev = nullptr;
			for (int i = 0; i < numNode - 1; i++) {
				if (newNode->operator<(*check)) {
					if (check == head) {
						head = newNode;
					}
					else {
						prev->next = newNode;
					}
					newNode->next = check;
					break;
				}
				else {
					prev = check;
					if (i == numNode - 2) {
						check->next = newNode;
						tail = newNode;
						break;
					}
					else {
						check = check->next;
					}
				}
			}
		}
	}
	// Implement this function
}

void LinkedList::clear() {
	if (numNode != 0) {
		Node* placeH;
		while (head != nullptr) {
			placeH = head->next;
			delete head;
			head = placeH;
		}
	}
}

Node* LinkedList::getHead() const {
	if (numNode != 0) {
		return head;
	}
	else {
		return nullptr;
	}
	// Implement this function it will be used to help grade other functions
}

string LinkedList::print() const {
	stringstream ss;
	Node* placeH = head;
	for (int i = 0; i < numNode; i++) {
		ss << placeH->data.id << " ";
		ss << placeH->data.year << " ";
		ss << placeH->data.month << " ";
		ss << placeH->data.temperature << endl;
		placeH = placeH->next;
	}
	return ss.str();
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
