#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <cstdlib>
#include <iostream>

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{
}
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::string cc;
	std::ifstream mapFile;
	mapFile.open(path);

	int srcX, srcY;
	
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			char denim = ',';

			if (x == sizeX - 1)
			{
				denim = '\n';
			}
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			//mapFile.get(c); 
			std::getline(mapFile, cc, denim);
			srcX = atoi(cc.c_str()) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			//mapFile.ignore();
		}
	}

	mapFile.ignore();
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '9')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.ignore();
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '8')
			{
				
				//Game::change = true;
			}
			mapFile.ignore();
		}
	}
	mapFile.close();

}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
		auto& tile(manager.addEntity());
		tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
		tile.addGroup(Game::groupMap);

}

