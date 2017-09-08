#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

class Window {
	int width, height;
	std::vector<std::string> menu_items;
	int menu_selected_item;
public:
	Window();	// resizes window
	void menu_down();
	void menu_up();
	std::string menu_get_name_selected();
	void draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers); // draws the level on screen (losmatrix)
	void draw_title();
};

#endif
