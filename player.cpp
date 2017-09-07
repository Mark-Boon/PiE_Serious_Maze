#include "player.h"

Player::Player(int x, int y, int los){
	this->x = x;
	this->y = y;
	this->los = los;
	//this->update_los_grid();
}

void Player::update_los_grid(Level* levelobject){
	int size = this->los*2+1;
// los_grid will be resized to the adjusted los (*2 because one can see the same distance backwards and +1 because thats the tile it's standing on) 
	this->los_grid.resize(size*size);
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			int x = this->x-this->los+j;	// 'x_player - los' to get to the left edge of the los_grid, '+j' to loop from left to right.
			int y = this->y-this->los+i;	// Same here but then for y coordinate.
			if(x<0 || y<0 || x>=levelobject->width || y>=levelobject->height)	// This is outside of the maze (occurs at the edges of the maze).
				this->los_grid[size*i+j] = 0;
			else
				this->los_grid[size*i+j] = levelobject->maze[y*levelobject->width+x];	// else copy the value of the maze at that coordinate.
		}
	}
}

void Player::go_up(){
	int size = this->los*2+1;
	if (this->los_grid[size*size/2-size]==0){
		this->y = y-1;
	}
}

void Player::go_down(){
	int size = this->los*2+1;
	if (this->los_grid[size*size/2+size]==0){
		this->y = y+1;
	}
}

void Player::go_left(){
	int size = this->los*2+1;
	if (this->los_grid[size*size/2-1]==0){
		this->x = x-1;
	}
}

void Player::go_right(){
	int size = this->los*2+1;
	if (this->los_grid[size*size/2+1]==0){
		this->x = x+1;
	}
}
