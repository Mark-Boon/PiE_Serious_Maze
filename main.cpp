#include "draw.h"

#include <iostream>
#include <windows.h>
#include <vector>


int main() {
	Window canvas;
	canvas.resize(20, 20);
	
	Player player;
	int size = player.getfov()*2+1;
	std::vector<int> matrix(size*size, 1);
	canvas.update(size, matrix);
	
	
	int i=1;
	while(!GetAsyncKeyState(VK_ESCAPE)){
		canvas.update(size, matrix);
		matrix[1] = i%2;
		i++;
		Sleep(500);
	}
	
	return 0;
}
