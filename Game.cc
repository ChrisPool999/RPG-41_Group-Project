#include <fstream>
#include <memory>
#include "Game.h"
#include "fruits.h"

GameState Game::getGameState() 
{
    return gameState;                       
}

MapTiles WorldMap::getMapTile(const std::pair<size_t, size_t> &pos) 
{
        return mapGrid[pos.first][pos.second];
}

void WorldMap::setMapTile(std::pair<size_t, size_t> &pos, MapTiles newTile) 
{
        mapGrid[pos.first][pos.second] = newTile;
}

void WorldMap::randomizeMap() 
{
    std::default_random_engine gen;
	std::uniform_int_distribution<int> d100(1,100);
	for (size_t i = 0; i < mapSize.first; i++) 
    {
		for (size_t j = 0; j < mapSize.second; j++) 
        {
			if (i == 0 || j == 0 || i == mapSize.first - 1 || j == mapSize.second - 1) 
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
    mapGrid[heroPosition.first][heroPosition.second] = MapTiles::HERO;
}

void Visuals::retrieveMap() 
{
    ;
}


void Visuals::draw(int x, int y) 
{
    ;
}
