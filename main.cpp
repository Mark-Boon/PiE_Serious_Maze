#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>

// Two game loops defined in main, one for the maze and one for the calculation screen:
void loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration);
void pick_number(Window* canvas, std::vector<int> collected_numbers, int frameduration);

int main() {
	int frameduration = 80;
	Window* canvas = new Window;
	
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
			running = false;
		}else if(GetAsyncKeyState(VK_DOWN) & 0x8000){
			canvas->next(canvas->menu_selected_item, canvas->menu_items);		//canvas->menu_down();
		}else if(GetAsyncKeyState(VK_UP) & 0x8000){
			canvas->previous(canvas->menu_selected_item, canvas->menu_items);		//canvas->menu_up();
		}else if(GetAsyncKeyState(VK_RETURN) & 0x8000){
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
				if (player->collected_numbers.empty() || player->collected_numbers[0] == 0)
					return 0;
				else
					running = false;
				//int time = GetTickCount();
					
				pick_number(canvas, player->collected_numbers, frameduration);	
		
				// maze loop ended by pressing escape, wait to not also exit titlescreen loop
				Sleep(200);			
			}
		}
		
		canvas->draw_title();
		
		while(GetTickCount()-time <frameduration ){}
	}
/*	running = true;
	// End-game while loop
	while (running){
		std::vector<char> calculation;
		int time = GetTickCount();
		// *** Hier iets met calc_screen	
		pick_number(canvas, numbers, frameduration, calculation);	
		
		
	}*/
	return 0;
}

void loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration){
	int size = player->los*2+1;
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		// When the player wants to quit abruptly, 'esc' can be used (0 in output vector will stop the game).
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) {return;}    
		else if(GetAsyncKeyState(VK_UP) & 0x8000) player->go_up();
		else if(GetAsyncKeyState(VK_DOWN) & 0x8000) player->go_down();
		else if(GetAsyncKeyState(VK_LEFT) & 0x8000) player->go_left();
		else if(GetAsyncKeyState(VK_RIGHT) & 0x8000) player->go_right();
		else if(GetAsyncKeyState(VK_RSHIFT) & 0x8000) return;
		
		player->update_los_grid(lvl);
		player->check_collision(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
}

void pick_number(Window* canvas, std::vector<int> collected_numbers, int frameduration){
	Sleep(200);
	bool running = true;
	int pick_order = 1;
	std::vector<std::string> chosen_numb_ops;
	while(running){
		int time = GetTickCount();
		
		// The actual screen
		canvas->draw_calc_screen(collected_numbers, pick_order, chosen_numb_ops);
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			running = false;
		switch(pick_order){
			case 1:{
				if(GetAsyncKeyState(VK_LEFT) & 0x8000){
					canvas->previous(canvas->calc_selected_item, collected_numbers);		
				}else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
					canvas->next(canvas->calc_selected_item, collected_numbers);			
				else if (GetAsyncKeyState(VK_RSHIFT) & 0x8000){
					// Does the following: put chosen number in vector, removes that number from collected numbers,
					// sets the 'select arrow' back to the first element, switches to choose from the operators vector
					chosen_numb_ops.push_back(std::to_string(canvas->calc_get_char(collected_numbers)));
					collected_numbers.erase(canvas->calc_selected_item);
					canvas->calc_selected_item = 0;
					pick_order = 2;
				}
			}
			break;
			case 2:{		
				if(GetAsyncKeyState(VK_LEFT) & 0x8000){
					canvas->previous(canvas->calc_selected_item,canvas->calc_items);		
				}else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
					canvas->next(canvas->calc_selected_item,canvas->calc_items);			
				else if (GetAsyncKeyState(VK_RSHIFT) & 0x8000){
					chosen_numb_ops.push_back(canvas->calc_items[canvas->calc_selected_item]);
					canvas->calc_selected_item = 0;
					pick_order = 1;
				}
			}
		}
		while(GetTickCount()-time <frameduration ){}	
	}
}

