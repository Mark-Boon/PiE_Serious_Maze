#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>


int main() {
	Level lvl1("lvl1.txt", 10);
	Level* lvl1p = &lvl1;

	Player player(3,4,3);
	int size = player.los*2+1;
	
	
	Window canvas;
	canvas.resize(size, size);
	
	int i=1;
	while(!GetAsyncKeyState(VK_ESCAPE)){
		player.update_los_grid( lvl1p );
		canvas.update(size, player.los_grid);
		player.update_player_location();
		Sleep(100);
	}
	
	return 0;
}
