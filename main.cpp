/*
* Serious Maze, a game about searching for, and calculations with numbers
* Authors:
* Mark Boon	(m.n.boon@student.utwente.nl)
* Lennart Knoll (l.j.knoll@student.utwente.nl)
* Date last changes: 11-sept-2017
* 
* How to use the program:
* Navigate through the menu and the maze with the arrow keys, press ESC to quit at any time, use ENTER to go to selected element.
* Only playable on windows at the moment.
* 
* Files:
* all files with a name of "lvl?.txt" where ? can be eny integer number are levels you can play
* Designing your own level, use # for a wall and . for an empty space, the numbers in the maze are randomly generated when starting a level.
* 
* Restrictions:
* Make sure the lvl is surrounded with walls (#) so that the player cannot escape the level.
* Also position (1,1) should is always the beginning of level, so there should be a '.' character.
* 
* Revisions:
* See https://github.com/DoveDoof/PiE_Serious_Maze
* 
* Error-management:
* Complete program is in command prompt, so any errors will appear there.
*/

#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <stdexcept>

// Two game loops defined in main, one for the maze and one for the calculation screen:
void loop_maze(Window* canvas, Level* lvl, Player* player, int frameduration);
void pick_number(Window* canvas, std::vector<int> collected_numbers, int frameduration);

int main() {
	try{
	int frameduration = 100;
	Window* canvas = new Window;
	
	bool running = true;
	while(running){
		int time = GetTickCount();
		
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
			running = false;
		}else if(GetAsyncKeyState(VK_DOWN) & 0x8000){
			canvas->next(canvas->menu_selected_item, canvas->menu_items);		
		}else if(GetAsyncKeyState(VK_UP) & 0x8000){
			canvas->previous(canvas->menu_selected_item, canvas->menu_items);		
		}else if(GetAsyncKeyState(VK_RETURN) & 0x8000){
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
	}catch (std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
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
		else if(GetAsyncKeyState(VK_RSHIFT) & 0x8000) break;
		
		player->update_los_grid(lvl);
		player->check_collision(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
	// If you collected nothing, just return to menu
	if (player->collected_numbers.empty() || player->collected_numbers[0] == 0)
		return;
	pick_number(canvas, player->collected_numbers, frameduration);
}

void pick_number(Window* canvas, std::vector<int> collected_numbers, int frameduration){
	Sleep(200);
	bool running = true;
	int pick_order = 1;
	std::vector<std::string> chosen_numb_ops;
	while(running){
		int time = GetTickCount();
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			running = false;
		// When there are 3 elements in chosen_numb_ops, the player picked 2 numbers and an operator, so a calculation has to be made.
		if(chosen_numb_ops.size()==3)
			canvas->calculator(chosen_numb_ops);
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
					collected_numbers.erase(collected_numbers.begin()+canvas->calc_selected_item);
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
		// The actual screen
		canvas->draw_calc_screen(collected_numbers, pick_order, chosen_numb_ops);
		while(GetTickCount()-time <frameduration){}	
	}
}

