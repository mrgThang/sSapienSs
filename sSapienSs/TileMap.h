
#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

#define MAX_TILES 20

class TileMap : public BaseTexture
{

};

class GameMap
{
public:
	GameMap();
	~GameMap();

	void LoadMap(const char* path, const int MAX_MAP_X, const int MAX_MAP_Y);

	bool LoadTileTexture(SDL_Renderer* screen, std::string s, int s_size);

	void HandleEvent(const int MAX_MAP_X);

	void DrawMap(SDL_Renderer* screen);

	void MoveLeft(const Uint8* currentKeyStates);

	void MoveRight(const Uint8* currentKeyStates, int MAX_MAP_X);

	int GetStatusMov()
	{
		return status_mov;
	}

	void StartAgain();

private:
	Map game_map;
	TileMap tile_map[MAX_TILES];
	int status_mov;
};

#endif