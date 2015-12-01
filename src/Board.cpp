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
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
            int typenum = randomInt(5,0);
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
	int xGen = randomInt(9,0);
	int yGen;
	if (human->enemy) {
		yGen = randomInt(1,0);
	} else {
		yGen = randomInt(9,8);
	}

	bool goodlocation = false;
	//make sure there are no other humans or boulders on the tile
	//if there is, choose another one
	while (!goodlocation) {
		goodlocation = checkLocation(board,xGen,yGen);
		if (!goodlocation) {
			xGen = randomInt(9,0);
			if (human->enemy) {
				yGen = randomInt(1,0);
			} else {
				yGen = randomInt(9,8);
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

Human* Board::adjPlayer(int xpos,int ypos) {
	if(0 <= xpos && xpos <= 9 && 0 <= ypos && ypos <= 9) {
		if(xpos < 9)
    		if(tiles[xpos+1][ypos].isOccupiedByPlayer())
        		return tiles[xpos+1][ypos].getCharacter();
    	if(ypos < 9)
    		if(tiles[xpos][ypos+1].isOccupiedByPlayer())
        		return tiles[xpos][ypos+1].getCharacter();
    	if(xpos > 0)
   			if(tiles[xpos-1][ypos].isOccupiedByPlayer())
        		return tiles[xpos-1][ypos].getCharacter();
    	if(ypos > 0)
    		if(tiles[xpos][ypos-1].isOccupiedByPlayer())
        		return tiles[xpos][ypos-1].getCharacter();
    	return nullptr;
    }
    return nullptr;
}

Human* Board::rangedTargetPlayer(int xpos, int ypos, int dexterity) {
	/*if(0 <= xpos && xpos <= 9 && 0 <= ypos && ypos <= 9) {
		for
	}*/
	return nullptr;
}

Human* Board::closestPlayer(int xpos, int ypos, Human *humans) {
	//calculate euclidean distance to all other players, choose shortest one
	//or something faster
	double minDistance = std::numeric_limits<double>::max();
	Human *closestPlayer;
	for (int i = 0; i < 6; i++) {
		if (!humans[i].enemy && humans[i].alive) {
			int distancex = xpos - humans[i].x;
			distancex *= distancex;
	  		int distancey = ypos - humans[i].y;
	  		distancey *= distancey;
	  		double calcDistance = sqrt(distancex + distancey);
	  		if (calcDistance <= minDistance) {
	  			minDistance = calcDistance;
	  			closestPlayer = &humans[i];
	  		}
	  	}
	}
	return closestPlayer;
	return &humans[0];
}
