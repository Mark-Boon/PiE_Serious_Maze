#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>

// Two game loops defined in main, one for the maze and one for the calculation screen:
std::vector<int> loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration);
void calc_screen(Window* canvas, std::vector<int> collected_numbers, int frameduration);

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
				std::vector<int>numbers = loop_maze(canvas, lvl, player, frameduration);
				if (numbers.empty() == 1)
					return 0;
				else if (numbers[0] == 0)
					return 0;
				// maze loop ended by pressing escape, wait to not also exit titlescreen loop
				Sleep(200);
				
				// *** Hier iets met calc_screen
				calc_screen(canvas, numbers, frameduration);
			}
		}
		
		canvas->draw_title();
		
		while(GetTickCount()-time <frameduration ){}
	}
	
	return 0;
}

std::vector<int> loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration){
	int size = player->los*2+1;
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		// When the player wants to quit abruptly, 'esc' can be used (0 in output vector will stop the game).
		if(GetAsyncKeyState(VK_ESCAPE)) {return {0};}    
		else if(GetAsyncKeyState(VK_UP)) player->go_up();
		else if(GetAsyncKeyState(VK_DOWN)) player->go_down();
		else if(GetAsyncKeyState(VK_LEFT)) player->go_left();
		else if(GetAsyncKeyState(VK_RIGHT)) player->go_right();
		else if(GetAsyncKeyState(VK_RSHIFT)) return player->collected_numbers;
		
		player->update_los_grid(lvl);
		player->check_collision(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
	return player->collected_numbers;
}

void calc_screen(Window* canvas, std::vector<int> collected_numbers, int frameduration){
	std::vector<std::string> calculation;
	bool running = true;
	while(running){
		int time = GetTickCount();
		bool pick_number = false;
		
		// First one needs to pick a number

			// The actual screen
		canvas->draw_calc_screen(collected_numbers);
		if(GetAsyncKeyState(VK_ESCAPE)){
			running = false;
		}else if(GetAsyncKeyState(VK_LEFT)){
			canvas->calc_left(collected_numbers);
		}else if(GetAsyncKeyState(VK_RIGHT))
			canvas->calc_right(collected_numbers);
		//else if (GetAsyncKeyState(VK_RSHIFT)) 
			// Select something ...

		while(GetTickCount()-time <frameduration ){}	
	}
}
