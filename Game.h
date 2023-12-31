#pragma once
#include <vector>
#include <iostream>

enum class MapTiles 
{
	HERO     = 'H',
	MONSTER  = 'M',
    WALL     = '#',
	WATER    = '~',
	OPEN     = '.',
	TREASURE = '$'
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

private:
    const MapCoordinates mapSize = {100, 100};
    MapCoordinates heroPosition = {50, 50};
    std::vector<std::vector<MapTiles>> mapGrid;
    void randomizeMap();
};

class Visuals 
{
public:
    int getDisplaySize();
    void draw(WorldMap&);

private:
    const int displaySize = 30;
};

class Game 
{
public:

private:
    WorldMap worldMap = WorldMap();
};