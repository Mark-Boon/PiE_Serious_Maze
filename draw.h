#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

class Window {
	// This is the width in characters, 1 width = 2 characters, height is just height
	int width, height;
public:
	void resize(int width, int height);	// resizes window in character dimensions
	void update(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers); // draws the level on screen (losmatrix)
};

#endif
