#include <iostream>
#include <fstream>
#include "functions.h"
using namespace std;

// Normally you should not use global variables. However, the stack is
//   limited in size and will not allow arrays of this size. We'll learn
//   later how to put these arrays on the heap instead. Regardless, for now
//   we'll use these and treat them as if they were declared in main. So
//   when used in functions, we'll pass them as we would any other array.
static int elevations[MAX_ROWS][MAX_COLS];
static Pixel image[MAX_ROWS][MAX_COLS];

int main() {
	using namespace std;

	ifstream file;
	ofstream outFile;
	int rows, cols, max, min;
	char filenameArr[100];

	//Lines 22-40 get input for number of rows, columns, and filename and then check if any of the inputs are invalid
	
	cin >> rows;
	if (cin.fail()) {
		cout << "Error: Problem reading in rows and columns." << endl;
	}
	cin >> cols;
	if (cin.fail()) {
		cout << "Error: Problem reading in rows and columns." << endl;
	}
	cin >> filenameArr;

	file.open(filenameArr);
	if (!(file.is_open())) {
		cout << "Error: Unable to open file " << filenameArr << endl;

		//system("pause");
	}
	else if (rows < 1 || cols < 1) {
		cout << "Error: Problem reading in rows and columns." << endl;
	}
	else {
		loadData(elevations, rows, cols, file);
		findMaxMin(elevations, rows, cols, max, min);

		loadGreyscale(image, elevations, rows, cols, max, min);

		int bestRow = 0;
		Pixel red = { 252, 25, 63 };
		Pixel green =  {31 , 253 , 13 };
		int elevChange = colorPath(elevations, image, rows, cols, red, 0);
		int elevCheck;

		for (int i = 1; i < rows; i++) {
			elevCheck = colorPath(elevations, image, rows, cols, red, i);
			if (elevCheck < elevChange) {
				elevChange = elevCheck;
				bestRow = i;
			}
		}

		colorPath(elevations, image, rows, cols, green, bestRow);

		//colorPath(elevations, image, rows, cols, red, 0);



		int len = 0;
		while (filenameArr[len] != '\0') { //calculates length of filename
			len++;
		}

		//adds ".ppm" to end of filename
		filenameArr[len] = '.';
		filenameArr[len + 1] = 'p';
		filenameArr[len + 2] = 'p';
		filenameArr[len + 3] = 'm';
		filenameArr[len + 4] = '\0';

		outFile.open(filenameArr);

		outputImage(image, rows, cols, outFile);


		//system("pause");
	}


}