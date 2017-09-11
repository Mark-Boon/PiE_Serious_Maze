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
	
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE)){
			running = false;
		}else if(GetAsyncKeyState(VK_DOWN)){
			canvas->menu_down();
		}else if(GetAsyncKeyState(VK_UP)){
			canvas->menu_up();
		}else if(GetAsyncKeyState(VK_RETURN)){
			// Get filename of selected level
			std::string filename = canvas->menu_get_name_selected();
			if(filename == "Quit"){
				running = false;
			}else {
				// level(filename, ratio nr generation)
				Level* lvl = new Level(filename , 5);
				// player(begin x, begin y, LOS, pointer to level)
				Player* player = new Player(1,1,8,lvl);
				// Open level loop
				loop_maze(canvas, lvl, player, frameduration);
				// maze loop ended by pressing escape, wait to not also exit titlescreen loop
				Sleep(200);
			}
		}
		
		canvas->draw_title();
		
		while(GetTickCount()-time <frameduration ){}
	}
	
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
		
		player->update_los_grid(lvl);
		player->check_collision(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
	
}
