

/*
 * TemperatureData.h
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#ifndef TEMPERATUREDATA
#define TEMPERATUREDATA

#include <string>

using namespace std;

struct TemperatureData {
	// Put data members here
	string id;
	int month;
	int year;
	double temperature;
	TemperatureData();
	TemperatureData(std::string id, int year, int month, double temperature);
	virtual ~TemperatureData();
	bool operator<(const TemperatureData& b);
};

#endif /* TEMPERATUREDATA */
