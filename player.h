#ifndef PLAYER
#define PLAYER
#include "read.h"

#include <vector>
#include <windows.h>

class Player{
public:
	// Player has x and y position and a line of sight (los)
	int x, y, los;
	// los_grid stands for 'line of sight grid' and is the part of the maze that is actually visible for the player
	std::vector<int> los_grid;
	// Keeps track of numbers collected in maze
	std::vector<int> collected_numbers;
	Level* lvlp;
	Player(int x, int y, int los, Level* lvlp);
	
	// Calculates visible cells surrounding player
	void update_los_grid(Level* levelobject);
	
	// Updates the location of the player
	void go_up();
	void go_down();
	void go_left();
	void go_right();
	void check_collision(Level* lvlp);

};


#endif
