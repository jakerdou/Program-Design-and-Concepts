#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node() {
	next = nullptr;

} // remember to initialize next to nullptr

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature) {
	data.id = id;
	data.year = year;
	data.month = month;
	data.temperature = temperature;
	next = nullptr;
}
// remember to initialize next to nullptr

bool Node::operator<(const Node& b) {
	if (this->data.id != b.data.id) {
		return (this->data.id < b.data.id);
	}
	else {
		if (this->data.year != b.data.year) {
			return (this->data.year < b.data.year);
		}
		else {
			if (this->data.month != b.data.month) {
				return (this->data.month < b.data.month);
			}
			else {
				return NULL;
			}
		}
	}
}
