#pragma once
#include "common.h"
#include "LTexture.h"
#include "PieceManager.h"
#include "Grid.h"
#include "GA.h"
#include "Vector2.h"

class Game
{
public:
	static Game* game()
	{
		if (sGame == NULL)
			sGame = new Game();
		
		return sGame;
	}
	
	bool loadMedia();
	void init();
	void close();
	void run();
	void clearRow(int clearY);

private:
	static Game* sGame;
	Game();
	~Game();

	Grid* grid;
	PieceManager* pieceManager;
	GA* ga;
	
	// Load the game's textures
	LTexture bgTex;

	// Load music and sound effects
	
	void update(int frames);
	void render();
};