#include <iostream>
#include "functions.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char** argv) {
	using namespace std;

	bool invFlag = false;
	int numFlag = 0;
	int numNewStr = 0;
	bool careCase = false;
	bool ignoreSpace = true;
	bool isPal = false;
	
	// checks for flags, keeps track of how many flags and if they are valid
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			bool isFlag = false;
			for (int j = 1; j < strlen(argv[i]); j++) {
				if (tolower(argv[i][j]) == 'c') {
					careCase = true;
					isFlag = true;
				}
				else if (tolower(argv[i][j]) == 's') {
					ignoreSpace = false;
					isFlag = true;
				}
				else {
					invFlag = true;
				}
			}
			if (isFlag) {
				numFlag++;
			}
		}
	}

	numNewStr = argc - numFlag - 1;


	// printUsageInfo if no inputs or if invalid flags
	if (numNewStr == 0 || invFlag == true) {
		cout << "Usage: " << argv[0] << " [-c] [-s] <term> ..." << endl;
		printUsageInfo(argv[0]);

	}
	// else runs program
	else {
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] != '-') {
				cout << "\"" << argv[i] << "\"" << " is";
				isPal = isPalindrome(argv[i], careCase, ignoreSpace); //checks if palindrome
				if (isPal == false) {
					cout << " not";
				}
				cout << " a palindrome." << endl;
			}
		}
	}
	return 0;
}