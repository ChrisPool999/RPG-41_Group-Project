#include <ncurses.h>
#include <unistd.h>
#include "Map.h"

void turn_on_ncurses() 
{
    initscr();//Start curses mode
    start_color(); //Enable Colors if possible
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //Set up some color pairs
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    clear();
    noecho();
    cbreak();
}

void turn_off_ncurses() {
    clear();
    endwin(); // End curses mode
    if (system("clear")) {}
}

int main() {
    constexpr int maxFPS = 90;
    WorldMap worldMap; 
    turn_on_ncurses();

	while (true) 
	{
        worldMap.draw();
        worldMap.getInput();
        worldMap.handleTileEvent();
	    usleep(1'000'000 / maxFPS);
    }
    return 0;
}
