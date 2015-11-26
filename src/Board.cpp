#include "Board.h"

Board::Board() {
	this->width = 10;
	this->height = 10;
	this->tiles = new Tile*[10];
	for(int i = 0; i < 10; ++i) {
    	tiles[i] = new Tile[10];
	}
	generate();
}

void Board::generate() {
	qsrand(time(NULL));
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
            int typenum = qrand()%(5+1);
			Terrain type;
			switch(typenum) {
				case 0:
					type = PLAIN;
					break;
				case 1: 
					type = PLAIN;
					break;
				case 2:
					type = PLAIN;
					break;
				case 3:
					type = BOULDER;
					break;
				case 4:
					type = WATER;
					break;
				case 5:
					type = WATER;
					break;
			}
			Tile tile(type);
			tiles[x][y] = tile;
		}
 	}
 	return;
}


Tile Board::get(int x, int y) {
	return tiles[x][y];
}

void Board::put(int x, int y, Tile tile) {
	tiles[x][y] = tile;
	return;
}

void Board::destroy() {
	delete [] tiles;
}

void generateLocation(Board *board, Human *human) {
	//min + (rand() % (int)(max - min + 1))
	int xGen = 0 + qrand()%(int)(9-0+1);
	int yGen;
	if (human->enemy) {
		yGen = 0 + qrand()%(int)(1-0+1);
	} else {
		yGen = 8 + qrand()%(int)(9-8+1);
	}

	bool goodlocation = false;
	//make sure there are no other humans or boulders on the tile
	//if there is, choose another one
	while (!goodlocation) {
		goodlocation = checkLocation(board,xGen,yGen);
		if (!goodlocation) {
			xGen = 0 + qrand()%(int)(9-0+1);
			if (human->enemy) {
				yGen = 0 + qrand()%(int)(1-0+1);
			} else {
				yGen = 8 + qrand()%(int)(9-8+1);
			}
		}
	}
	human->x = xGen;
	human->y = yGen;
	board->tiles[xGen][yGen].setCharacter(human);
	return;
}

bool checkLocation(Board *board, int x, int y) {
	bool goodlocation = true;
	if (x < 0 || x > 9 || y < 0 || y > 9) {
			goodlocation = false;
	} else if (board->tiles[x][y].getType() == BOULDER) {
			goodlocation = false;
	} else if (board->tiles[x][y].isOccupied()) {
		goodlocation = false;
	}
	return goodlocation;
}
