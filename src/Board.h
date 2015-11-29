#ifndef BOARD
#define BOARD

#include <iostream>
#include <string>
#include <cstdlib>
#include <qglobal.h>
#include "Human.h"
#include "Tile.h"

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
    int adjPlayer(int xpos,int ypos);
};

void generateLocation(Board *board, Human *human);
bool checkLocation(Board *board, int x, int y);

#endif
