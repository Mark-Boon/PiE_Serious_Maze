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
			std::string temp = canvas->menu_get_name_selected();
			if(temp == "Quit"){
				running = false;
			}else {
				// Create filename string of selected level
				std::string filename = "lvl";
				filename += temp[6];
				filename += ".txt";
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
		player->check_collision(lvl);
		player->update_los_grid(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
	
}
