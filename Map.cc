#include <fstream>
#include <memory>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
#include "Map.h"
#include "fruits.h"

WorldMap::WorldMap() 
{
	mapGrid = std::vector<std::vector<MapTiles>> (mapSize.row, std::vector<MapTiles>(mapSize.col, MapTiles::OPEN));
	randomizeMap(); // can optimize these two lines to only create the map one time,
}

MapCoordinates WorldMap::getMapSize() 
{
	return mapSize;
}

MapTiles WorldMap::getMapTile(const MapCoordinates &pos) 
{
        return mapGrid[pos.row][pos.col];
}

MapCoordinates WorldMap::getHeroPosition() 
{
	return heroPosition;
}

void WorldMap::setMapTile(MapCoordinates pos, MapTiles newTile)
{ 
        mapGrid[pos.row][pos.col] = newTile;
}

void WorldMap::randomizeMap() 
{
    std::default_random_engine gen;
	std::uniform_int_distribution<int> d100(1,100);
	for (int i = 0; i < mapSize.row; i++) 
    {
		for (int j = 0; j < mapSize.col; j++) 
        {
			if (i == 0 || j == 0 || i == mapSize.row - 1 || j == mapSize.col - 1) 
            {
				mapGrid[i][j] = MapTiles::WALL; 
            }
			else 
            {
				if (d100(gen) <= 5) 
                {
					mapGrid[i][j] = MapTiles::MONSTER;
				}
				else if (d100(gen) <= 3) 
                {
					mapGrid[i][j] = MapTiles::TREASURE;
				}
				else if (d100(gen) <= 10) 
                {
					mapGrid[i][j] = MapTiles::WALL;
				}
				else if (d100(gen) <= 3) 
                {
					mapGrid[i][j] = MapTiles::WATER;
				}
				else if (d100(gen) <= 40) 
                {
					if (mapGrid[i-1][j] == MapTiles::WATER ||
                        mapGrid[i+1][j] == MapTiles::WATER ||
                        mapGrid[i][j-1] == MapTiles::WATER ||
                        mapGrid[i][j+1] == MapTiles::WATER) 
					{
						mapGrid[i][j] = MapTiles::WATER;
					}
				}
			}
		}
	}
    mapGrid[heroPosition.row][heroPosition.col] = MapTiles::HERO;
}

std::pair<int, int> WorldMap::getColDisplayBoundaries()
{
	int colStart = getHeroPosition().col - (displaySize / 2);
	int colEnd = getHeroPosition().col + (displaySize / 2);
	
	if (colStart < 0) 
	{
		colEnd -= colStart;
		colStart = 0;							
	}
	if (colEnd > getMapSize().col - 1) 
	{
		colStart -= (colEnd - (getMapSize().col - 1));
		colEnd = getMapSize().col - 1;
	}
	return {colStart, colEnd};
}

std::pair<int, int> WorldMap::getRowDisplayBoundaries()
{
	int rowStart = getHeroPosition().row - (displaySize / 2);
	int rowEnd   = getHeroPosition().row + (displaySize / 2);

	if (rowStart < 0) 
	{
		rowEnd -= rowStart;
		rowStart = 0;
	}
	if (rowEnd > getMapSize().row - 1) 
	{
		rowStart -= (rowEnd - (getMapSize().row - 1));
		rowEnd = getMapSize().row - 1;
	}
	return {rowStart, rowEnd};
}

int WorldMap::getTileColor(MapCoordinates pos) // BUG:: WHAT IF THEY DONT REQUEST EXISTING COLOR
{
	switch (getMapTile(pos))
	{
		case MapTiles::WALL:
			return 5;
		case MapTiles::WATER:
			return 2;
		case MapTiles::HERO:
			return 3;
		case MapTiles::TREASURE:
			return 4;
		case MapTiles::MONSTER:
			return 6;
		default:
			return -1;
	}	
}

void WorldMap::draw() 
{
		int rowStart = getRowDisplayBoundaries().first; 
		int rowEnd = getRowDisplayBoundaries().second;
		int colStart = getColDisplayBoundaries().first;
		int colEnd = getColDisplayBoundaries().second;

		for (int i = rowStart; i <= rowEnd; i++) 
		{
			for (int j = colStart; j <= colEnd; j++) 
			{
				if (i == getHeroPosition().row && j == getHeroPosition().col) 
				{
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i - rowStart, j - colStart, 'H');
					attroff(A_UNDERLINE | A_BOLD);
				}
				else 
				{
					int color = getTileColor({i, j});				
					attron(COLOR_PAIR(color));
					mvaddch(i - rowStart, j - colStart, static_cast<char>(getMapTile({i, j})));
					attroff(COLOR_PAIR(color));
				}
			}
		}
		mvprintw(displaySize + 1, 0, "X: %i Y: %i\n", getHeroPosition().col, getHeroPosition().row);
		refresh();
};

void WorldMap::waitForInput()
{
	while (true) 
	{
		Controls input = static_cast<Controls>(getch()); // BUG: if getch isnt a Controls it will be undefined behavior
		switch (input)
		{
			case Controls::RIGHT:
				heroPosition.col = std::min(heroPosition.col + 1, getMapSize().col - 1);
				break;
			case Controls::LEFT:
				heroPosition.col = std::max(0, heroPosition.col - 1);
				break;
			case Controls::UP:
				heroPosition.row = std::max(0, heroPosition.row - 1);
				break;
			case Controls::DOWN:
				heroPosition.row = std::min(heroPosition.row + 1, getMapSize().row - 1);
				break;
			case Controls::ESC:
				// BUG: need to add stuff to fix terminal
				// exit(0);
			default:
				break;
		}

		draw();

		switch (getMapTile({heroPosition.row, heroPosition.col})) 
		{
			case MapTiles::MONSTER:
				setMapTile({heroPosition.row, heroPosition.col}, MapTiles::OPEN);
				break;
			case MapTiles::TREASURE:
				setMapTile({heroPosition.row, heroPosition.col}, MapTiles::OPEN);
				break;
			case MapTiles::WATER:
				;
				break;
			case MapTiles::WALL:
				;
				break;
			default:
				break;
		}
		usleep(1'000'000/maxFPS);
    }
}