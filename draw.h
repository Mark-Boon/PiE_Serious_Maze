#ifndef DRAW
#define DRAW

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

class Window {
	int width, height;
public:
	void resize(int width, int height);	// resizes window
	void update(int width, std::vector<int> &losmatrix); // updates screen with level info
};

#endif
