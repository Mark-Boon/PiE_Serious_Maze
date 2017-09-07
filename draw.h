#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

class Window {
	int width, height;
	std::vector<std::string> menu_items;
public:
	Window();	// resizes window
	void draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers); // draws the level on screen (losmatrix)
	void draw_title();
};

#endif
