#include <iostream>
#include <istream>
#include <fstream>
#include <cmath>
#include "functions.h"
#include <cstring>
using namespace std;

void findMaxMin(const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int& max, int& min) {
	max = elevations[1][1];
	min = elevations[1][1];
	for (int i = 0; i < rows; i++) {
		//finds max and min of inputted data
		for (int j = 0; j < cols; j++) {
			if (elevations[i][j] > max) {
				max = elevations[i][j];
			}
			else if (elevations[i][j] < min) {
				min = elevations[i][j];
			}
		}
	}
}

void loadData(int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, istream& inData) {
	using namespace std;

	int numPoints = 0;
	int errVal = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (errVal == 0) {
				inData >> elevations[i][j];
				if (inData.fail()) { //checks if any of the input failed
					errVal = 2;
				}
				
			}
		}
	}

	int check;
	inData >> check;
	if (!(inData.fail())) {
		errVal = 3;
	}

	//lines 50-56 check for errors and output the appropriate output
	if (errVal == 3) {
		//cout << "Error: Problem reading in rows and columns." << endl;
		cout << "Error: Too many data points" << endl;
	}
	else if (errVal == 2) {
		cout << "Error: End of file reached prior to getting all required data." << endl;
	}
}

int scaleValue(int value, int max, int min) {
	int scaleVal;
	scaleVal = round((((value - min) / ((1.0)*(max - min))) * 255));
	return scaleVal;
}

void loadGreyscale(Pixel image[MAX_ROWS][MAX_COLS], const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int max, int min) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//passes in value from scaleValue function and sets that as the RGB value for the pixel
			image[i][j].blue = scaleValue(elevations[i][j], max, min);
			image[i][j].red = scaleValue(elevations[i][j], max, min);
			image[i][j].green = scaleValue(elevations[i][j], max, min);
		}
	}
}

void outputImage(const Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, ostream& outData) {
	outData << "P3" << endl << cols << " " << rows << endl << "255" << endl;
	for (int i = 0; i < rows; i++) {
		//outputs RGB data to ppm file
		for (int j = 0; j < cols; j++) {
			outData << image[i][j].red << " " << image[i][j].green << " " << image[i][j].blue << " ";
		}
		outData << endl;
	}
}



int colorPath(const int elevations[MAX_ROWS][MAX_COLS], Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, Pixel color, int start_row) {
	using namespace std;

	int NEChange, EChange, SEChange;
	int nextCol, NRow, SRow, min;
	int elevChange = 0;
	char dir;

	/*image[start_row][1] = color; //NEED TO CHANGE BACK TO ZERO and change the next 2 rows
	image[0][43] = color;
	image[1][43] = color;*/

	image[start_row][0] = color;

	for (int col = 0; col < cols-1; col++) { //need to change col back to 0
		NEChange = 10000000, SEChange = 10000000;
		nextCol = col + 1; 
		if (start_row != 0) {
			NRow = start_row - 1;
			NEChange = abs(elevations[start_row][col] - elevations[NRow][nextCol]);
		}
		if (start_row != (rows - 1)) {
			SRow = start_row + 1;
			SEChange = abs(elevations[start_row][col] - elevations[SRow][nextCol]);
		}
		EChange = abs(elevations[start_row][col] - elevations[start_row][nextCol]);
		
		//lines 113-169 assign minimum elevation change

		dir = 'E';

		if (SEChange < EChange && NEChange >= SEChange) {
			dir = 'S';
		}
		else if (NEChange < SEChange && NEChange < EChange) {
			dir = 'N';
		}
		
		//colors in pixel
		switch (dir) {
		case 'E':
			image[start_row][nextCol] = color;
			min = EChange;
			break;
		case 'N':
			image[NRow][nextCol] = color;
			min = NEChange;
			start_row = start_row - 1;
			break;
		case 'S':
			image[SRow][nextCol] = color;
			min = SEChange;
			start_row = start_row + 1;
			break;
		}
		

		elevChange = elevChange + min;
	}
	return elevChange;
}

