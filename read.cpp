#include "read.h"

Level::Level(std::string filename){
// First part of the constructor: determine the dimensions of the level.
	// Every object in 'Level' stores its given filename in member variable 'filename'.
	this->filename = filename;
	std::fstream file_maze;
	file_maze.open(filename);
	// First check whether the file is opened.
	if (file_maze.is_open()){
		char n;
		int width=0;
		int height=1;
		// Read through entire file.
		while (file_maze>>n){
			width++;
			// Keep track of number of free spaces in maze
			if (n=='.')
				this->spaces++;
			// If we encounter \n, there must be a new line so height +1.
			if (file_maze.peek()=='\n')
				height++;
		}
		width/=height;
		file_maze.close();
		this->width=width;
		this->height=height;
		// Define the size of the maze vector.
		this->maze.resize(width*height);
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
			if (n=='#')
				this->maze[i]=-1;
			else if (n=='.')
				this->maze[i]=0;
			i++;	
		}
		file_maze.close();
	}else std::cout<<"Error opening file"<<std::endl;
	
	// Generate numbers in maze with ratio to available spaces of 1/10
	generate_numbers();
}

void Level::generate_numbers(){
	srand(time(NULL));
	// because this is an integer, it is rounded down
	int nr_nr = this->spaces/10;
	for (int i=0; i<nr_nr; i++){
		int pos = rand()%(this->height*this->width);
		while(this->maze[pos]!=0){
			pos = rand()%(this->height*this->width);
		}
		this->maze[pos] = rand()%9+1;
	}
}
