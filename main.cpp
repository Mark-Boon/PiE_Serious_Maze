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
		
		player->update_los_grid(lvl);
		player->check_collision(lvl);
		canvas->draw_maze(size, player->los_grid, player->collected_numbers);
		
		while(GetTickCount()-time <frameduration ){}
	}
	
}
