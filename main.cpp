#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>


int main() {
	Level lvl1("lvl1.txt", 10);
	Level* lvl1p = &lvl1;

	Player player(3,4,3);
	int size = player.los*2+1;
	
	Window canvas;
	canvas.resize(size, size);
	
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE)) running = false;
		else if(GetAsyncKeyState(VK_UP)) player.go_up();
		else if(GetAsyncKeyState(VK_DOWN)) player.go_down();
		else if(GetAsyncKeyState(VK_LEFT)) player.go_left();
		else if(GetAsyncKeyState(VK_RIGHT)) player.go_right();
		
		player.update_los_grid( lvl1p );
		canvas.update(size, player.los_grid);
		
		while(GetTickCount()-time <80 ){}
	}
	
	return 0;
}
