#ifndef DRAW
#define DRAW

#include <vector>
class Window {
	int width, height;
public:
	void resize(int width, int height);
	void update(int size, std::vector<int> &fovmatrix);
};

class Player{
	int x=1, y=1;
public:
	int fov = 2;
	int getx(){return x;}
	int gety(){return y;}
	int getfov(){return fov;}
};

#endif
