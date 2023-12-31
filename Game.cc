#include <fstream>
#include <memory>
#include <ncurses.h>
#include "Game.h"
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

int Visuals::getDisplaySize() 
{
	return displaySize;
}

void Visuals::draw(WorldMap &worldMap) 
{
		int x         = worldMap.getHeroPosition().row;
		int y         = worldMap.getHeroPosition().col;
		int mapHeight = worldMap.getMapSize().row;
		int mapWidth  = worldMap.getMapSize().col;

		int start_x   = x - (displaySize / 2);
		int end_x     = x + (displaySize / 2);
		int start_y   = y - (displaySize / 2);
		int end_y     = y + (displaySize / 2);

		if (start_x < 0) 
		{
			end_x -= start_x;
			start_x = 0;							
		}
		if (start_y < 0) 
		{
			end_y -= start_y;
			start_y = 0;
		}
		if (end_x > mapWidth - 1) 
		{
			start_x -= (end_x - (mapWidth - 1));
			end_x = mapWidth - 1;
		}
		if (end_y > mapHeight - 1) 
		{
			start_y -= (end_y - (mapHeight - 1));
			end_y = mapHeight - 1;
		}

		for (int i = start_y; i <= end_y; i++) 
		{
			for (int j = start_x; j <= end_x; j++) 
			{
				if (i == y && j == x) 
				{
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i - start_y, j - start_x, 'H');
					attroff(A_UNDERLINE | A_BOLD);
				}
				else 
				{
					int color = 1;
					
					switch (worldMap.getMapTile({i, j}))
					{
						case MapTiles::WALL:
							color = 5;
							break;

						case MapTiles::WATER:
							color = 2;
							break;

						case MapTiles::HERO:
							color = 3;
							break;

						case MapTiles::TREASURE:
							color = 4;
							break;

						case MapTiles::MONSTER:
							color = 6;
							break;
							
						default:
							break;
					}					
					attron(COLOR_PAIR(color));
					mvaddch(i - start_y, j - start_x, static_cast<char>(worldMap.getMapTile({i, j})));
					attroff(COLOR_PAIR(color));
				}
			}
		}
};
