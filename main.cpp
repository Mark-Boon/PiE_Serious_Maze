#include "read.h"
#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>


int main() {
	Level lvl1("lvl1.txt");
	Level* lvl1p = &lvl1;
	
	Player player(1,1,7);
	int size = player.los*2+1;
	
	
	Window canvas;
	canvas.resize(size, size);
	
	int i=1;
	while(!GetAsyncKeyState(VK_ESCAPE)){
		player.update_los_grid( lvl1p );
		canvas.update(size, player.los_grid);
		Sleep(100);
	}
	
	return 0;
}
