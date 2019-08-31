#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>

bool isPalindrome(char* newString, bool careCase, bool ignoreSpace);

void adjustPalString(char* newString, bool careCase, bool ignoreSpace);

void removePunctuation(char* newString);

void removeSpaces(char* newString);

void removeCase(char* newStrings);

bool isPalindromeR(char* newString);

void printUsageInfo(char* name);

#endif

