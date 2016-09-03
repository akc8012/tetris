#pragma once
#include "common.h"
#include "LTexture.h"
#include "PieceManager.h"
#include "Grid.h"
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

private:
	static Game* sGame;
	Game();
	~Game();

	Grid* grid;
	PieceManager* pieceManager;
	
	// Load the game's textures
	LTexture bgTex;

	// Load music and sound effects
	
	void update(int frames);
	void render();
};