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
	bool enableGA() { return enableGAFlag; }
	bool doBlinks() { return doBlinksFlag; }

private:
	static Game* sGame;
	Game();
	~Game();

	Grid* grid;
	PieceManager* pieceManager;
	GA* ga;
	int gaTicks;
	bool enableGAFlag = true;
	bool doBlinksFlag = true;

	
	// Load the game's textures
	LTexture bgTex;

	// Load music and sound effects
	
	void update(int frames);
	void render();
};