#include <iostream>
#include <string>
#include <ncurses.h>
#include "baseobjects.h"
using namespace std;


int main() {
	Board board(15,15);
	//base game loop
	initscr();
	refresh();
	getch();
	endwin();

	return 0;
}

