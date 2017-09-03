#ifndef DRAW
#define DRAW

#include <vector>
class Window {
	int width, height;
public:
	void resize(int width, int height);
	void update(int size, std::vector<int> &fovmatrix);
};

#endif
