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
	Player(int x, int y, int los);
	
	// Calculates visible cells surrounding player
	void update_los_grid(Level* levelobject);
	
	// Updates the location of the player after a move button has been pressed.	
	void update_player_location();

};


#endif
