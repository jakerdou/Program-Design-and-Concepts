#include "TemperatureDatabase.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	string location;
	int year;
	int month;
	double temp;
	fstream file;
	file.open(filename);
	if (!file.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
	}
	else {
		while (!(file.eof())) {
			bool failVal = false;

			file >> location;
			if (cin.fail()) { cout << "Error: Other invalid input" << endl; failVal = true; }

			file >> year;
			if (cin.fail()) { cout << "Error: Other invalid input" << endl; failVal = true; }

			file >> month;
			if (cin.fail()) { cout << "Error: Other invalid input" << endl; failVal = true; }

			file >> temp;
			if (cin.fail()) { cout << "Error: Other invalid input" << endl; failVal = true; }

			if (failVal == false) {
				records.insert(location, year, month, temp);
			}
			
		}	
	}

	
	// Implement this function for part 1
}

void TemperatureDatabase::performQuery(const string& filename) {
	//Initialize variables
	string location, typeQ, line;
	int year1, year2;
	ifstream qFile;
	ofstream rFile;
	rFile.open("result.dat");
	//Open file and check that it opened
	qFile.open(filename);
	if (!(qFile.is_open())) {
		cout << "Error: Unable to open " << filename << endl;
	}
	else {
		while (!(qFile.eof())) {
			bool failVal = false;
			//Read whole to check for incorrect number on each line
			getline(qFile, line);
			stringstream SS(line);

			//Read values and check if any failed
			SS >> location;
			if (SS.fail()) { cout << "Error: Other invalid query" << endl; failVal = true; }

			SS >> typeQ;
			if (SS.fail()) { cout << "Error: Other invalid query" << endl; failVal = true; }

			SS >> year1;
			if (SS.fail()) { cout << "Error: Other invalid query" << endl; failVal = true; }

			SS >> year2;
			if (SS.fail()) { cout << "Error: Other invalid query" << endl; failVal = true; }

			//check if year is invalid
			if (!failVal) {
				if (year1 < 1800 || year1>2018 || year1 > year2 || year2 < 1800 || year2>2018) {
					cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
					failVal = true;
				}
			}
			
			//if code has not failed yet, calculate either mode or average
			if (!failVal) {
				if (typeQ == "MODE") {
					rFile << location << " " << year1 << " " << year2 << " " << typeQ << " ";
					int mode = getMode(location, year1, year2);
					//Check if mode was invalid
					if (mode < -50 || mode > 50 || mode == 0) {
						rFile << "unknown" << endl;
					}
					else {
						rFile << mode << endl;
					}
				}
				else if (typeQ == "AVG") {
					rFile << location << " " << year1 << " " << year2 << " " << typeQ << " ";
					double avg = getAvg(location, year1, year2);
					//check if average was invalid
					if (avg < -50.0 || avg > 50.0 || (avg >= 0 && avg < .001)) {
						rFile << "unknown" << endl;
					}
					else {
						rFile << avg << endl;
					}
				}
				//if type of query is not average or mode
				else {
					cout << "Error: Unsupported query " << typeQ << endl;
				}
			}
		}
	}


	// Implement this function for part 2
	//  Leave it blank for part 1
} 

int TemperatureDatabase::getMode(string location, int year1, int year2) {
	Node* curr = records.getHead();
	vector<int> modeVec;
	while (curr->data.id != location) {
		if (curr->next == nullptr) {
			break;
		}
		else {
			curr = curr->next;
		}
		
	}
	while (curr->data.year < year1 && curr->data.id == location) {
		curr = curr->next;
	}
	while (curr->data.year <= year2 && curr->data.id == location && curr != nullptr) {
		double temp;
		temp = curr->data.temperature + .5;
		int tempInt = (int)temp;
		modeVec.push_back(tempInt);
		if (curr->next != nullptr) {
			curr = curr->next;
		}
		else {
			break;
		}
	}
	int mode = 0;
	int numInst = 0, mostInst = 0;
	for (int i = 0; i < modeVec.size(); i++) {
		for (int j = 0; j < modeVec.size(); j++) {
			if (modeVec.at(i) == modeVec.at(j)) {
				numInst++;
			}
		}
		if (numInst > mostInst || (numInst == mostInst && modeVec.at(i) > mode)) {
			mostInst = numInst;
			mode = modeVec.at(i);
		}
		numInst = 0;
	}


	return mode;
}

double TemperatureDatabase::getAvg(string location, int year1, int year2) {
	Node* curr = records.getHead();
	vector<double> avgVec;
	if (curr != nullptr) {
		while (curr->data.id != location) {
			if (curr->next == nullptr) {
				break;
			}
			else {
				curr = curr->next;
			}
		}
		while (curr->data.id == location && curr->data.year < year1) {
			curr = curr->next;
		}
		while (curr->data.year <= year2 && curr->data.id == location && curr != nullptr) {
			double temp;
			temp = curr->data.temperature;
			avgVec.push_back(temp);
			if (curr->next != nullptr) {
				curr = curr->next;
			}
			else {
				break;
			}
		}
		double avg = 0.0;
		for (int i = 0; i < avgVec.size(); i++) {
			avg = avg + avgVec.at(i);
		}
		if (avgVec.size() > 0) {
			avg = avg / avgVec.size();
		}
		return avg;
	}
	return 0;
}
