#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>


int main() {
	Level lvl1("lvl1.txt", 10);
	Level* lvlp = &lvl1;

	// player(begin x, begin y, LOS, pointer to level)
	Player player(3,4,3,lvlp);
	int size = player.los*2+1;
	
	Window canvas;
	canvas.resize(size, size);
	
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE)) {running = false; break;}
		else if(GetAsyncKeyState(VK_UP)) player.go_up();
		else if(GetAsyncKeyState(VK_DOWN)) player.go_down();
		else if(GetAsyncKeyState(VK_LEFT)) player.go_left();
		else if(GetAsyncKeyState(VK_RIGHT)) player.go_right();
		player.check_collision();
		
		player.update_los_grid( lvlp );
		canvas.update(size, player.los_grid);
		
		while(GetTickCount()-time <80 ){}
	}
	
	return 0;
}
