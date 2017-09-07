#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>

void loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration);

int main() {
	int frameduration = 80;
	Window* canvas = new Window;
	
	while(!GetAsyncKeyState(VK_ESCAPE)){
		int time = GetTickCount();
		
		canvas->draw_title();
		
		while(GetTickCount()-time <frameduration ){}
	}
	
	Level* lvl = new Level("lvl2.txt", 5);
	
	// player(begin x, begin y, LOS, pointer to level)
	Player* player = new Player(3,4,3,lvl);
	
	loop_maze(canvas, lvl, player, frameduration);
	HWND hWnd;
	PostMessage(hWnd, WM_CLOSE, 0, 0);
	return 0;
}

void loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration){
	int size = player->los*2+1;
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE)) {running = false; break;}
		else if(GetAsyncKeyState(VK_UP)) player->go_up();
		else if(GetAsyncKeyState(VK_DOWN)) player->go_down();
		else if(GetAsyncKeyState(VK_LEFT)) player->go_left();
		else if(GetAsyncKeyState(VK_RIGHT)) player->go_right();
		player->check_collision(lvl);
		player->update_los_grid(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
	
}
