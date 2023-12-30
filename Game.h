#pragma once
#include <vector>
#include <iostream>

enum class GameState 
{
    intro,
    overworld,
    combat
};

enum class MusicState 
{
    intro,
    overworld,
    combat,
    combatEncounter,
    combatWon,
    combatLost,
    treasureEncounter,
    gameWon
};

enum class MapTiles 
{
	HERO     = 'H',
	MONSTER  = 'M',
	WALL     = '#',
	WATER    = '~',
	OPEN     = '.',
	TREASURE = '$'
};

class Game 
{
public:
    GameState getGameState();

private:
    WorldMap worldMap = WorldMap();
    GameState gameState = GameState::intro;
};

class WorldMap 
{
public:
	MapTiles getMapTile(const std::pair<size_t, size_t>&);
	void setMapTile(std::pair<size_t, size_t>&, MapTiles);

private:
    constexpr static std::pair<size_t, size_t> mapSize = {100, 100};
    constexpr static std::pair<size_t, size_t> heroPosition = {50, 50};
    std::vector<std::vector<MapTiles>> mapGrid;
    void randomizeMap();
};

// class Controls 
// {

// };

class Visuals 
{
    void retrieveMap();
    void draw(int, int);
};

class Audio 
{

};

class Entities 
{

};

class Heroes : Entities 
{

};

class Enemies : Entities 
{

};