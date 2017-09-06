#include "draw.h"


void Window::resize(int width, int height){
	/* TODO
	std::stringstream ss;
	ss << "mode " << 40 << "," << 20;
	const char* temp = ss.str().c_str();
	std::cout << temp;
	*/
	this->width = 50;
	this->height = 30;

	// Code taken and modified from: https://stackoverflow.com/questions/7552644/resize-cmd-window
	system("mode 50,30");   //Set mode to ensure window does not exceed buffer size
  	SMALL_RECT WinRect = {0, 0, 50, 30};   //New dimensions for window in 8x12 pixel chars
  	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &WinRect);   //Set new size for window
}

void Window::update(int width, std::vector<int> &losmatrix){
	std::stringstream ss;
	for (int i=0; i<losmatrix.size(); i++){
		if (i%width==0 && i!=0)
			ss << '\n';
		if (i == width*width/2)					//This is the location of the player.
			ss << (char) 120 << (char) 120;	
		else if (losmatrix[i]==-1)
			ss << (char) 178 << (char) 178;
		else
			ss << (char) 32 << (char) 32;
	}
	// Fill screen up with newlines
	for (int i=0; i<= (this->height-width-1); i++)
		ss << '\n';
	std::cout << ss.str();
}
