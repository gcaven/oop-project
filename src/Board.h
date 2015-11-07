#include "Tile.h"

class Board {
private:
	Tile** tiles;
	int width;
	int height;
	void generate();

public:
	Board(int width, int height);
	Tile get(int x, int y);
	void put(int x, int y, Tile tile);
	int index(int x, int y);
	void destroy();
};
