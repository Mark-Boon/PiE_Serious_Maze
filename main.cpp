#include "player.h"
#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>


int main() {
	
	Player player(1,1,7);
	int size = player.fov*2+1;
	
	std::vector<int> matrix(size*size, 1);
	
	Window canvas;
	canvas.resize(size, size);
	
	int i=1;
	while(!GetAsyncKeyState(VK_ESCAPE)){
		canvas.update(size, matrix);
		Sleep(100);
	}
	
	return 0;
}
