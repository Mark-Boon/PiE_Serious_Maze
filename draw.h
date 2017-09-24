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
#include <stdexcept>


class Window {
	// This is the width in characters, 1 width = 2 characters, height is just height
	int width, height;
	
public:
	int menu_selected_item;
	std::vector<std::string> menu_items;
	int calc_selected_item;
	std::vector<std::string> calc_items;
	
	Window();	// resizes window
	
	// This template function is defined in the header of 'draw', because the header needs
	// the argument of a parameter, which is not defined for a template.
	// The function is used to scroll through options in the menu screen/collected numbers in calculation screen
	template<typename T>
	void next(int &itemselect,std::vector<T> &itemlist){
		if(itemselect == itemlist.size()-1)
			itemselect = 0;
		else
			itemselect++;
	}
		template<typename T>
	void previous(int &itemselect,std::vector<T> &itemlist){
		if(itemselect == 0)
			itemselect = itemlist.size()-1;
		else
			itemselect--;
	}
	
	void get_list_levelfiles();
	std::string menu_get_name_selected();
	void draw_title();
	
	// This function is used in the maze screen
	void draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers); // draws the level on screen (losmatrix)

	// These functions are used in the calculation screen
	int calc_get_char(std::vector<int> &collected_numbers);
	void draw_calc_screen(std::vector<int> collected_numbers, int pick_order,std::vector<std::string> chosen_numb_ops);
	void calculator(std::vector<std::string> &chosen_numb_ops);
};

#endif
