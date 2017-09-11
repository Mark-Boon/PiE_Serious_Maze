#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>

// Two game loops defined in main, one for the maze and one for the calculation screen:
std::vector<int> loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration);
void pick_number(Window* canvas, std::vector<int> collected_numbers, int frameduration, std::vector<char> calculation);

int main() {
	int frameduration = 80;
	Window* canvas = new Window;
	
	bool running = true;
	std::vector<int>numbers;
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
				numbers = loop_maze(canvas, lvl, player, frameduration);
				if (numbers.empty() == 1)
					return 0;
				else if (numbers[0] == 0)
					return 0;
				else
					running = false;
				// maze loop ended by pressing escape, wait to not also exit titlescreen loop
				Sleep(200);			
			}
		}
		
		canvas->draw_title();
		
		while(GetTickCount()-time <frameduration ){}
	}
	running = true;
	// End-game while loop
	while (running){
		std::vector<char> calculation;
		int time = GetTickCount();
		// *** Hier iets met calc_screen	
		pick_number(canvas, numbers, frameduration, calculation);	
		
		
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

void pick_number(Window* canvas, std::vector<int> collected_numbers, int frameduration, std::vector<char> calculation){
	bool running = true;
	while(running){
		int time = GetTickCount();
		int pick_order = 1;
		// The actual screen
		canvas->draw_calc_screen(collected_numbers, pick_order);
		if(GetAsyncKeyState(VK_ESCAPE)){
			running = false;
		}else if(GetAsyncKeyState(VK_LEFT)){
			canvas->calc_left(collected_numbers);
		}else if(GetAsyncKeyState(VK_RIGHT))
			canvas->calc_right(collected_numbers);
		else if (GetAsyncKeyState(VK_RSHIFT)){
			calculation.push_back(canvas->calc_selected_item);
			pick_order = 2;
			return;
		}
		while(GetTickCount()-time <frameduration ){}	
	}
}

//void pick_operator(
