/*
 * TemperatureData.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */


#include "TemperatureData.h"
#include <string>
using namespace std;

TemperatureData::TemperatureData() {
	id = "";
	year = 0;
	month = 0;
	temperature = 0;
} //initialize everything

TemperatureData::TemperatureData(std::string id, int year, int month, double temperature) {

	this->month = month;
	this->year = year;
	this->temperature = temperature;
	this->id = id;
	
} //initialize everything


TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b) {
	if (this->id != b.id) {
		return (this->id < b.id);
	}
	else {
		if (this->year != b.year) {
			return (this->year < b.year);
		}
		else {
			if (this->month != b.month) {
				return (this->month < b.month);
			}
			else {
				return NULL;
			}
		}
	}
}

