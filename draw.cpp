#include "draw.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

void Window::resize(int width, int height){
	// Code taken and modified from: https://stackoverflow.com/questions/7552644/resize-cmd-window
	system("mode 80,25");   //Set mode to ensure window does not exceed buffer size
  	SMALL_RECT WinRect = {0, 0, width*2-1, height-1};   //New dimensions for window in 8x12 pixel chars
  	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &WinRect);   //Set new size for window
}

void Window::update(int size, std::vector<int> &fovmatrix){
	std::stringstream ss;
	for (int i=0; i<fovmatrix.size(); i++){
		if (i%size==0)
			ss << '\n';
		if (fovmatrix[i])
			ss << (char) 178 << (char) 178;
		else
			ss << (char) 32 << (char) 32;
	}
	std::cout << ss.str();
}
