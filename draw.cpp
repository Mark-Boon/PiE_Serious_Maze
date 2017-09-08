#include "draw.h"


void Window::resize(int width, int height){
	/* TODO
	std::stringstream ss;
	ss << "mode " << 40 << "," << 20;
	const char* temp = ss.str().c_str();
	std::cout << temp;
	*/
	this->width = 25;
	this->height = 30;

	// Code taken and modified from: https://stackoverflow.com/questions/7552644/resize-cmd-window
	system("mode 50,30");   //Set mode to ensure window does not exceed buffer size
  	SMALL_RECT WinRect = {0, 0, 50, 30};   //New dimensions for window in 8x12 pixel chars
  	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &WinRect);   //Set new size for window
}

void Window::update(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers){
	std::stringstream ss;
	std::string temp;
	
	// Margin top
	int top_margin = (this->width - width)/2;
	// Appends an integer (top_margin) times the character given.
	temp.append<int>(top_margin, '\n');
	ss << temp;
	
	// Calculate size of margin
	int size_margin = this->width - width;
	temp.clear();
	temp.append<int>(size_margin, ' ');
	// Show the line of sight matrix of the player
	for (int i=0; i<losmatrix.size(); i++){
		if (i%width==0)
			ss << '\n' << temp;
		if (i == width*width/2)					// This is the location of the player.
			ss << (char) 218 << (char) 191;	
		else if (losmatrix[i]==-2)
			ss << (char) 177 << (char) 177;
		else if (losmatrix[i]==-1)
			ss << (char) 219 << (char) 219;
		else if (losmatrix[i]==0)
			ss << (char) 32 << (char) 32;
		else ss << (char) 32 << losmatrix[i];	// This copies the numbers that need to be collected.
	}
	
	// Fill below los_grid untill text
	temp.clear();
	temp.append<int>(top_margin, '\n');
	ss << temp;
	
	// Show collected numbers on the screen
	ss << "\n Numbers collected: \n ";
	std::vector<int>::iterator it;
	it = collected_numbers.begin();
	while (it !=collected_numbers.end()){	// Loop through collected_numbers
		ss << *it << " ";
		++it;
	}
	
	// Fill screen up with newlines
	int bot_margin = this->height - this->width  - 2;
	temp.clear();
	temp.append<int>(bot_margin, '\n');
	ss << temp;
	
	std::cout << ss.str();
}
