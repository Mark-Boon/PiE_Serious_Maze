#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <direct.h>
#include <string>
#define GetCurrentDir _getcwd

class Window {
	// This is the width in characters, 1 width = 2 characters, height is just height
	int width, height;
	std::vector<std::string> menu_items;
	int menu_selected_item;
public:
	Window();	// resizes window
	void get_list_levelfiles();
	void menu_down();
	void menu_up();
	std::string menu_get_name_selected();
	void draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers); // draws the level on screen (losmatrix)
	void draw_title();
};

#endif
