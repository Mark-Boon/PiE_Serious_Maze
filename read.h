#ifndef READ_H
#define READ_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>


// declarations
class Level
{
private:	
	std::string filename;
public:
	Level(std::string filename);								// Constructor which has build-in dimensions.
	int width, height;											//	Width and height of the maze.
	std::vector<int> maze;
};

#endif
