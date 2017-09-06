#ifndef READ_H
#define READ_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include <ctime>


// declarations
class Level
{
private:
	int spaces = 0;
	std::string filename;
	void generate_numbers();
public:
	Level(std::string filename);								// Constructor which has build-in dimensions.
	int width, height;											//	Width and height of the maze.
	std::vector<int> maze;
};

#endif
