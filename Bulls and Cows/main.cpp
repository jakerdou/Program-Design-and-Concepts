/*
James Robinson
CSCE 121 Bulls and Cows

This code takes an input of an integer, 
and then takes the input of an integer trying to guess a number,
informing you of how close your number is to that number.

A cow means that your number matches,
while a bull means that your number is the same and in the correct position.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>

using namespace std;


int main() {
	srand(std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count() % 2000000000);
	// needed to autograde some test cases in Mimir

		int numDig;
		int* codeArray = NULL; //use pointer so that memory can be dynamically allocated
		int codeNumDig = 0;
		int code;
		int sameVal = 1; // value that tells if there are duplicate numbers in array
		int breakNum = 0; //number to tell places to break

		cout << "Enter number of digits in code (3, 4 or 5): ";
		cin >> numDig;
		
		while (sameVal == 1) {
			int numIt = 0; // number of iterations
			int digDiff = 10000; //set so high because the difference in digits won't get that high
				while (digDiff > 1) { //makes sure that the difference in digits isnt larger than 1, so that there can only be 1 leading zero
					codeArray = new int[numDig]; //initializes array
					
					digDiff = 0;
					codeNumDig = 0;

					// gets input of number
					if (numDig > 0) {
						code = rand() % static_cast <int> (pow(10, numDig)); // generates random code
					}
					else if (numDig == 0) {
						cout << "Enter code: ";
						cin >> code;
						cout << "Enter number of digits in code: ";
						cin >> numDig;

						// initializes array
						codeArray = new int[numDig];
					}
					while (pow(10, codeNumDig) < code) { // figures out how many digits in inputted number
						codeNumDig++;
					}
					digDiff = numDig - codeNumDig;
					if (digDiff == 1) { //loads leading zero into array
						codeArray[0] = 0;
					}
				}
			
			// iterates through number and makes sure that no number is the same
			for (int j = 0; j < codeNumDig; j++) {

				int first; // variables first, second, and third were technically unnecessary, but one of my calculations was lengthy so I broke it up into 3 parts
				int second;
				int third;
				int answer;
				int i = 0;

				first = code % static_cast<int>((pow(10, numDig - digDiff - j)));
				second = code % static_cast<int>((pow(10, numDig - digDiff - j - 1)));
				third = static_cast<int>((pow(10, numDig - digDiff - j - 1)));
				answer = (first - second) / third;

				for (i; i < (numIt+digDiff); i++) { //if the number is the same as one before it, the loop breaks and starts over
					if (answer == codeArray[i]) {
						breakNum = 1;
						break;
					}
				}
				if (i == (numIt+digDiff)) { //if it does not match a previous entry, its loaded into the array
					numIt++;
					codeArray[digDiff + j] = answer;
				}
				else if (breakNum == 1) {
					break;
				}
			}
			if ((numIt+digDiff) == numDig) { //if all the numbers were unique, it stops the while loop
				sameVal = 0;
			}
		}

		//outputs correct output
		cout << "Number to guess: ";
		for (int i = 0; i < numDig; i++) {
			cout << codeArray[i];

			if (i != numDig - 1) {
				cout << "-";
			}
		}
		cout << endl;

		//begin code pertaining to part 2
		int* guessArray = NULL;
		int cows = 0;
		int bulls = 0;

		while (bulls != numDig) {
			int guess;
			int guessSameVal = 1; // value that tells if there are duplicate numbers in array
			int guessBreakNum = 0; //number to tell places to break
			int guessNumDig;

			while (guessSameVal == 1) {

				int guessNumIt = 0; // number of iterations
				int guessDigDiff = 10000;
				while (guessDigDiff > 1) { //makes sure that the difference in digits isnt larger than 1, so that there can only be 1 leading zero
					guessNumDig = 0;
					guessArray = new int[numDig];
					guessDigDiff = 0;

					cout << "Enter Guess: ";
					cin >> guess;

					//calculates number of digits in guess
					while (pow(10, guessNumDig) < guess) { // figures out how many digits in inputted number
						guessNumDig++;
					}
					guessDigDiff = numDig - guessNumDig;
					if (guessDigDiff > 1) {
						cout << "Each number must be different." << endl;
					}
					else if (guessDigDiff < 0) {
						cout << "You can only enter " << numDig << " digits." << endl;
					}

					if (guessDigDiff == 1) { //loads leading zero into array
						guessArray[0] = 0;
					}
				}

				// iterates through guess and makes sure no numbers are the same
				for (int j = 0; j < guessNumDig; j++) { //iterates through digits of random number

					int first; // variables first, second, and third were technically unnecessary, but one of my calculations was lengthy so I broke it up into 3 parts
					int second;
					int third;
					int answer;
					int i = 0;

					first = guess % static_cast<int>((pow(10, numDig - guessDigDiff - j)));
					second = guess % static_cast<int>((pow(10, numDig - guessDigDiff - j - 1)));
					third = static_cast<int>((pow(10, numDig - guessDigDiff - j - 1)));
					answer = (first - second) / third;

					for (i; i < (guessNumIt + guessDigDiff); i++) { //if the number is the same as one before it, the loop breaks and starts over
						if (answer == guessArray[i]) {
							cout << "Each number must be different." << endl;
							guessBreakNum = 1;
							break;
						}
					}
					if (i == (guessNumIt + guessDigDiff)) { //if it does not match a previous entry, its loaded into the array
						guessNumIt++;
						guessArray[guessDigDiff + j] = answer;
					}
					else if (guessBreakNum == 1) {
						break;
					}
				}
				if (guessNumIt == guessNumDig) { //if all the numbers were unique, it stops the while loop
					guessSameVal = 0;
				}
			}

			//begin code calculating how many bulls and cows
			cows = 0;
			bulls = 0;
			for (int i = 0; i < numDig; i++) {
				for (int j = 0; j < numDig; j++) {
					if (codeArray[i] == guessArray[j]) {
						cows++;
					}
					if (codeArray[i] == guessArray[j] && i == j) {
						bulls++;
						cows--;
					}
				}
			}
			if (bulls != numDig) {
				cout << bulls << " bulls" << endl;
				cout << cows << " cows" << endl;
			}
		}

		//output for correct guess
		cout << numDig << " bulls... ";
		for (int i = 0; i < numDig; i++) { //outputs correct output
			cout << codeArray[i];
			if (i != numDig - 1) {
				cout << "-";
			}
		}
		cout << " is correct!" << endl;
}
