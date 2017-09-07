#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>

//void loop_maze(canvas);

int main() {
	Window* canvas = new Window;
	
	Level* lvlp = new Level("lvl2.txt", 5);
	
	// player(begin x, begin y, LOS, pointer to level)
	Player* player = new Player(3,4,3,lvlp);
	int size = player->los*2+1;
	
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE)) {running = false; break;}
		else if(GetAsyncKeyState(VK_UP)) player->go_up();
		else if(GetAsyncKeyState(VK_DOWN)) player->go_down();
		else if(GetAsyncKeyState(VK_LEFT)) player->go_left();
		else if(GetAsyncKeyState(VK_RIGHT)) player->go_right();
		player->check_collision(lvlp);
		
		player->update_los_grid( lvlp );
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <100 ){}
	}
	
	return 0;
}
