#include "read.h"

Level::Level(std::string filename, int ratio){
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
	} else {
		throw(std::invalid_argument("Error opening file"));
	}
	
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
	}else throw(std::invalid_argument("Error opening file"));
	
	// Generate numbers in maze with ratio to available spaces of 1/ratio
	generate_numbers(ratio);
}

void Level::generate_numbers(int ratio){
	// Generates seed for later use of rand()
	srand(time(NULL));
	// Calculates number of numbers to be put in maze, because this is an integer, it is rounded down.
	int nr_nr = this->spaces/ratio;
	// Number of random numbers to be used for generating a target, rounded down
	int nr_target = nr_nr/5;
	int target[nr_target];
	
	// rand()%10 generates a number on interval [0,9]
	for (int i=0; i<nr_nr; i++){
		int pos = rand()%(this->height*this->width);
		// choose different spot to put number in if either there is a wall (maze[pos]=1) or pos is starting place of player
		while(this->maze[pos]!=0 || pos==this->width+1){
			pos = rand()%(this->height*this->width);
		}
		// Insert random number in maze at pos
		this->maze[pos] = rand()%9+1;
		// Use first few numbers to generate target later
		if(i<nr_target)
			target[i] = this->maze[pos];
	}
	
	// Store first number in level::target
	this->target = (float) target[0];
	// Loop through the rest to generate the target of the level you have to get close to for the best score
	for (int i=1; i<nr_target;i++){
		// Choose operator
		switch(rand()%4){
		case 0:
			this->target += target[i];
			break;
		case 1:
			this->target -= target[i];
			break;
		case 2:
			this->target *= target[i];
			break;
		case 3:
			this->target /= target[i];
			break;
		}
	}
}
