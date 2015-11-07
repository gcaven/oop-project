#include <iostream>
#include <string>
#include <cstdlib>
#include <qglobal.h>
#include "Board.h"

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
	this->tiles = new Tile*[width];
	for(int i = 0; i < width; ++i) {
    	tiles[i] = new Tile[height];
	}
	generate();
}

void Board::generate() {
    qsrand(time(NULL));
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
            int typenum = qrand()%(8+1);
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
					type = HILL;
					break;
				case 4:
					type = TREES;
					break;
				case 5:
					type = DITCH;
					break;
				case 6:
					type = BOULDER;
					break;
				case 7:
					type = WATER;
					break;
				case 8:
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
