#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

class Window {
	int width, height;
public:
	void resize(int width, int height);	// resizes window in character dimensions
	void update(int width, std::vector<int> &losmatrix); // draws the level on screen (losmatrix)
};

#endif
