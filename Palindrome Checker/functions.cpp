#include <iostream>
#include "functions.h"
#include "stdio.h"
#include "string.h"

bool isPalindrome(char* newString, bool careCase, bool ignoreSpace) {
	using namespace std;
	bool isPal;

	removePunctuation(newString);

	//checks flags and sees if string needs to be modified
	if (careCase == false || ignoreSpace == true) { 
		adjustPalString(newString, careCase, ignoreSpace);
	}
	
	isPal = isPalindromeR(newString);

	return isPal;
}


void adjustPalString(char* newString, bool careCase, bool ignoreSpace) {
	using namespace std;

	//checks flags and modifies string as needed

	if (ignoreSpace == true) { //
		removeSpaces(newString);
	}

	if (careCase == false) {
		removeCase(newString);
	}
}

void removePunctuation(char* newString) {
	using namespace std;
	for (int i = 0; i < strlen(newString); i++) { //iterates through and removes punctuation
		if (ispunct(newString[i])) {
			for (int j = i; j < strlen(newString); j++) {
				newString[j] = newString[j + 1];
			}
		}
	}
}

void removeSpaces(char* newString) {
	using namespace std;
	for (int i = 0; i < strlen(newString); i++) { //iterates through and removes spaces
		if (isspace(newString[i])) {
			for (int j = i; j < strlen(newString); j++) { 
				if (isspace(newString[j + 1])) { //checks for 2 spaces right next to each other
					for (int k = j; k < strlen(newString); k++) {
						newString[k] = newString[k + 1];
					}
				}
				newString[j] = newString[j + 1];
			}
		}
	}
}

void removeCase(char* newString) {
	using namespace std;
	for (int i = 0; i < strlen(newString); i++) {//iterates through and makes all lower case
		newString[i] = tolower(newString[i]);
	}
}

bool isPalindromeR(char* newString) {
	using namespace std;

	char newStringCopy[500];

	strcpy(newStringCopy, newString); 
	//copys string into new string because for whatever reason Mimir can't grade it otherwise

	bool isPal;
	int start = 0;
	int end = strlen(newStringCopy) - 1;

	if (newStringCopy[start] == newStringCopy[end]) { //checks if first and last are true
		isPal = true;
		for (int i = 0; i < end; i++) { //deletes first and last characters
			newStringCopy[i] = newStringCopy[i + 1];
		}
		newStringCopy[end - 1] = '\0';
		if (strlen(newStringCopy) > 1) {
			if (isPalindromeR(newStringCopy)) { //calls function recursively
				isPal = true;
			}
			else {
				isPal = false;
			}
		}
	}
	else {
		isPal = false;
	}
	return isPal;
}

void printUsageInfo(char* name) {
	using namespace std;
	//cout << "Usage: " << name << " [-c] [-s] <term> ..." << endl;
	cout << "  -c: turn on case sensitivity" << endl;
	cout << "  -s: turn off ignoring spaces" << endl;
}

