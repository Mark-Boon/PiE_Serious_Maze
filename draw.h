#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

class Window {
	// This is the width in characters, 1 width = 2 characters, height is just height
	int width, height;
	std::vector<std::string> menu_items;
	int menu_selected_item;
	int calc_selected_item;
public:
	Window();	// resizes window
	
	// These four functions are used in the menu screen (self-explainatory names)
	void menu_down();
	void menu_up();
	std::string menu_get_name_selected();
	void draw_title();
	
	// This function is used in the maze screen
	void draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers); // draws the level on screen (losmatrix)

	// These functions are used in the calculation screen
	void calc_left(std::vector<int> &collected_numbers);
	void calc_right(std::vector<int> &collected_numbers);
	int calc_get_char(std::vector<int> &collected_numbers);
	void draw_calc_screen(std::vector<int> collected_numbers);
	
};

#endif
