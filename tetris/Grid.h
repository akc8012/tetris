#pragma once
#include "common.h"
#include "Vector2.h"
#include "LTexture.h"

class Grid
{
public:

	Grid();
	~Grid();

	void setGrid(Vector2<int> pos, int shape);
	void setTempGrid(Vector2<int> pos, int shape);
	int getFitClearTemp();
	bool checkGrid(Vector2<int> pos);
	void printGrid();
	void loadMedia();
	void render();
	void clearGrid();
	bool isBlinking() { return blinking == Blinking; }

private:
	
	bool checkRows(int grid[][GRID_WIDTH], bool sendMsg = true);
	void clearRow(int grid[][GRID_WIDTH], int clearY, bool sendMsg);
	void initTempGrid();

	int clearCount = 0;
	int blinkCount = 0;
	int rowBlinking = -1;
	const int blinkRate = 26;

	enum BlinkState { Blinking, DoneBlinking, NotBlinking };
	BlinkState blinking = NotBlinking;

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

	int TEMP_GRID[GRID_HEIGHT][GRID_WIDTH] =
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	};

	Vector2<int> rotOff[4] = { Vector2<int>(0, -1), Vector2<int>(0, 0), Vector2<int>(-1, 0), Vector2<int>(-1, -1) };
};