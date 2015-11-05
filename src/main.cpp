#include <iostream>
#include <string>
#include <ncurses.h>
#include "baseobjects.h"

//this is just testing logic and shit, we need to create a ui
void game() {
	Board board = Board(15,15);
	std::cout << "  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14\n";
	for (int x=0; x<15; x++) {
		std::cout << x << ": ";
		for (int y=0; y<15; y++) {
			Tile tile = board.get(x,y);
			std::cout << tile.getTypeAsString() << " ";
		}
		std::cout << "\n";
	}
	board.destroy();
	return;
}

int main() {
	//base game loop
	game();
	return 0;
}

