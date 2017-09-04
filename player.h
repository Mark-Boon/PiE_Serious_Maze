#ifndef PLAYER
#define PLAYER
#include "read.h"

#include <vector>

class Player{
public:
	//Player has x and y position and a line of sight (los)
	int x, y, los;
	std::vector<int> los_grid;
	Player(int x, int y, int los);
	
	// Calculates visible cells surrounding player
	void update_los_grid(Level* levelobject);
};


#endif
