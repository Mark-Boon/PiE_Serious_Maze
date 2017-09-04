#include "player.h"

Player::Player(int x, int y, int los){
	this->x = x;
	this->y = y;
	this->los = los;
	//this->update_los_grid();
}

void Player::update_los_grid(Level* levelobject){
	int size = this->los*2+1;
	
	this->los_grid.resize(size*size);
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			int x = this->x-this->los+j;
			int y = this->y-this->los+i;
			if(x<0 || y<0 || x>=levelobject->width || y>=levelobject->height)
				this->los_grid[size*i+j] = 0;
			else
				this->los_grid[size*i+j] = levelobject->maze[y*levelobject->width+x];
		}
	}
}
