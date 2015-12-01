#ifndef BOARD
#define BOARD

#include <iostream>
#include <string>
#include <cstdlib>
#include <qglobal.h>
#include <limits>
#include <math.h>
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
    Human* adjPlayer(int xpos,int ypos);
    Human* rangedTargetPlayer(int xpos, int ypos, int dexterity);
    Human* closestPlayer(int xpos, int ypos, Human *humans);
};

void generateLocation(Board *board, Human *human);
bool checkLocation(Board *board, int x, int y);

#endif
