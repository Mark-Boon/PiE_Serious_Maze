#include "read.h"

Level::Level(std::string filename){
// First part of the constructor: determine the dimensions of the level.
	this->filename = filename;				// Every object in 'Level' stores its given filename in member variable 'filename'.
	std::fstream file_maze;
	file_maze.open(filename);
	if (file_maze.is_open()){				// First check whether the file is opened.
		char n;
		int width=0;
		int height=1;
		while (file_maze>>n){				// Read through entire file.
			width++;	
			if (file_maze.peek()=='\n')		// If we encounter \n, there must be a new line so height +1.
				height++;
		}
		width/=height;
		file_maze.close();
		this->width=width;
		this->height=height;
		this->maze.resize(width*height);	// Define the size of the maze vector.
	}
	else std::cout<<"Error opening file"<<std::endl;
// Second part of the constructor: load the information of the maze.
// Because we initially don't know what the size of the maze is, we first read the dimensions, then create a vector with the right dimension
// and then read the file again to fill in the ones and zeroes (for walls and paths respectively) in the vector 'maze'.
	file_maze.open(filename);
	if (file_maze.is_open()){				// First check whether the file is opened.
		char n;
		int i=0;
		while(file_maze>>n){
			if (n=='x')
				this->maze[i]=1;
			else if (n=='o')
				this->maze[i]=0;
		
			i++;	
		}
		file_maze.close();
	}else std::cout<<"Error opening file"<<std::endl;	
}	


	
	
