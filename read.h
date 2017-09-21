#ifndef READ_H
#define READ_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include <ctime>
#include <stdexcept>


// declarations
class Level
{
private:
	// Counts number of free cells in maze
	int spaces = 0;
	std::string filename;
	// Integer argument ratio: ratio of free cells to numbers on free cells
	// determines how many numbers should be placed in maze (e.g. 10 gives ratio 1:10)
	void generate_numbers(int);
public:
	Level(std::string filename, int);								// Constructor which has build-in dimensions.
	int width, height;											//	Width and height of the maze.
	std::vector<int> maze;
};

#endif
