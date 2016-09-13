#pragma once
#include "common.h"
#include "Vector2.h"
#include "LTexture.h"

struct Block
{
	Shape shape;
	int rot;

	void render(LTexture* tex, Vector2<int> pos)
	{
		tex->render(pos.x, pos.y, 0, rot);
	}
};

class Grid
{
public:

	Grid();

	void setGrid(Vector2<int> pos, int shape);
	bool checkGrid(Vector2<int> pos);
	void printGrid();
	void loadMedia();
	void render();

private:
	
	bool checkRows();
	void clearRow(int clearY);

	LTexture IBlockTex;
	LTexture JBlockTex;
	LTexture LBlockTex;
	LTexture OBlockTex;
	LTexture SBlockTex;
	LTexture TBlockTex;
	LTexture ZBlockTex;
	LTexture IBlock1Tex;
	LTexture IBlock2Tex;

	LTexture* textures[9] = { &IBlockTex, &JBlockTex, &LBlockTex, &OBlockTex, &SBlockTex, 
		&TBlockTex, &ZBlockTex, &IBlock1Tex, &IBlock2Tex };

	int GRID[GRID_HEIGHT][GRID_WIDTH] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	Vector2<int> rotOff[4] = { Vector2<int>(0, -1), Vector2<int>(0, 0), Vector2<int>(-1, 0), Vector2<int>(-1, -1) };
};