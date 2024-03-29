
#include <iostream>
#include <string>
#include <random>
#include "gl_stuff.h"
#include "Array2D.h"
#include <tbb/tbb.h>

using namespace std;
using namespace tbb;

#pragma region Function Prototypes

void initPattern(); // Initialise grid with "alive" and "dead" cell patterns
void update(); // Main update function - apply Game of Life rules here

#pragma endregion

const int ALIVE = 1;
const int DEAD = 0;
const int ARRSIZE = 75;

//
// Example array
//
Array2D<int> myArray = Array2D<int>(ARRSIZE, ARRSIZE);
int updateArray[ARRSIZE][ARRSIZE];

// Starting point for our program...
int main(int argc, char* argv[]) {
	gl_init(argc, argv, update, "CIS6007 WRIT1 - Game of Life Demo", true);
	initPattern();
	glutMainLoop();
	return 0;
}

void initPattern() {
	for (int x = 0; x < myArray.w; x++) {
		for (int y = 0; y < myArray.h; y++) {
			//double random = (double)rand() / (RAND_MAX); // Gives a number between 1 and 0;
			//myArray(x, y) = random > .5 ? 1 : 0; // 50% chance of being on
			myArray(x, y) = DEAD;
		}
	}
/*
	myArray(3, 2) = ALIVE;
	myArray(4, 3) = ALIVE;
	myArray(4, 4) = ALIVE;
	myArray(3, 4) = ALIVE;
	myArray(2, 4) = ALIVE;

	*/
		//pulsar
		myArray(1, 5) = ALIVE;
	myArray(1, 6) = ALIVE;
	myArray(2, 5) = ALIVE;
	myArray(2, 6) = ALIVE;
	myArray(11, 5) = ALIVE;
	myArray(11, 6) = ALIVE;
	myArray(11, 7) = ALIVE;
	myArray(12, 4) = ALIVE;
	myArray(12, 8) = ALIVE;
	myArray(13, 3) = ALIVE;
	myArray(13, 9) = ALIVE;
	myArray(14, 3) = ALIVE;
	myArray(14, 9) = ALIVE;
	myArray(15, 6) = ALIVE;
	myArray(16, 4) = ALIVE;
	myArray(16, 8) = ALIVE;
	myArray(17, 5) = ALIVE;
	myArray(17, 6) = ALIVE;
	myArray(17, 7) = ALIVE;
	myArray(18, 6) = ALIVE;
	myArray(21, 3) = ALIVE;
	myArray(21, 4) = ALIVE;
	myArray(21, 5) = ALIVE;
	myArray(22, 3) = ALIVE;
	myArray(22, 4) = ALIVE;
	myArray(22, 5) = ALIVE;
	myArray(23, 2) = ALIVE;
	myArray(23, 6) = ALIVE;
	myArray(25, 1) = ALIVE;
	myArray(25, 2) = ALIVE;
	myArray(25, 6) = ALIVE;
	myArray(25, 7) = ALIVE;
	myArray(35, 3) = ALIVE;
	myArray(35, 4) = ALIVE;
	myArray(36, 3) = ALIVE;
	myArray(36, 4) = ALIVE;
}

int countNeighbours(int x, int y) {
	int countNeighbours = 0;
	for (int x1 = -1; x1 <= 1; x1++) {
		for (int y1 = -1; y1 <= 1; y1++) {
			if (x1 == 0 && y1 == 0) {
				continue;
			}
			if ((myArray((x + x1 + 1),y)>= myArray.w)) 
			{
				continue;
			}
			if (myArray(x + x1, y + y1) == ALIVE) {
				countNeighbours++;
			}
		}
	}
	return countNeighbours;
}

void update() {
	/*for (int x = 0; x < myArray.w; x++) {
		for (int y = 0; y < myArray.h; y++) {
			
			bool targetState = myArray(x, y) == ALIVE;
			updateArray[x][y] = targetState ? ALIVE : DEAD;

			int neighbours = countNeighbours(x, y);
			//cout << myArray(x, y);
			if (x + 1 >= myArray.w)
			{
			continue;
			}

			if (targetState && neighbours < 2) updateArray[x][y] = DEAD;
			if (targetState && neighbours > 3) updateArray[x][y] = DEAD;
			if (!targetState && neighbours == 3) updateArray[x][y] = ALIVE;
		}
	}
	*/
tbb::parallel_for(tbb::blocked_range2d<int>(0, myArray.w, 0, myArray.h),
	[&](const tbb::blocked_range2d<int>& range) {
	for (int x = range.rows().begin(), x_end = range.rows().end(); x < x_end; x++) {
		for (int y = range.rows().begin(), y_end = range.rows().end(); y < y_end; y++) {
			bool targetState = myArray(x, y) == ALIVE;
			updateArray[x][y] = targetState ? ALIVE : DEAD;

			int neighbours = countNeighbours(x, y);
			//cout << myArray(x, y);
			if (x + 1 >= myArray.w)
			{
				continue;
			}

			if (targetState && neighbours < 2) updateArray[x][y] = DEAD;
			if (targetState && neighbours > 3) updateArray[x][y] = DEAD;
			if (!targetState && neighbours == 3) updateArray[x][y] = ALIVE;
		}
	}
	
}

); for (int row = 0; row < myArray.w; row++) {
		for (int column = 0; column < myArray.h; column++) {
			myArray(row, column) = updateArray[row][column];
		}
	}

	renderLatestGeneration(myArray);
}



