#pragma once
#include <vector>
#include <iostream>
#include <random> 

enum class MapTiles 
{
	HERO     = 'H',
	MONSTER  = 'M',
    WALL     = '#',
	WATER    = '~',
	OPEN     = '.',
	TREASURE = '$'
};

enum class Controls 
{
	ESC = 27,
	UP = 65, 
	DOWN = 66,
	RIGHT = 67,
	LEFT = 68
};

struct MapCoordinates 
{
    int col;
    int row;
};

class WorldMap 
{
public:
    WorldMap();
    MapCoordinates getMapSize();
	MapTiles getMapTile(const MapCoordinates&);
    MapCoordinates getHeroPosition();
	void setMapTile(MapCoordinates, MapTiles); // ??? This feels like the class should handle any tile setting...   
    void draw();    
    void getInput();
    void checkForTileEvent();

private:
    const int maxFPS = 90;
    const MapCoordinates mapSize = {100, 100};
    MapCoordinates heroPosition = {50, 50};
    std::vector<std::vector<MapTiles>> mapGrid;
    const int displaySize = 30;
    void randomizeTile(std::default_random_engine&, std::uniform_int_distribution<int>&, MapCoordinates);
    void randomizeMap();
    std::pair<int, int> getColDisplayBoundaries();
    std::pair<int, int> getRowDisplayBoundaries();
    int getTileColor(MapCoordinates);
};