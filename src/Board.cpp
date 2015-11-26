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
