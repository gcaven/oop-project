#include "Tile.h"
#ifndef BOARD
#define BOARD

class Board {
private:
	int width;
	int height;
	void generate();

public:
	Tile** tiles;
	Board();
	Tile get(int x, int y);
	void put(int x, int y, Tile tile);
	int index(int x, int y);
	void destroy();
};

#endif
