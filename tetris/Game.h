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

	PieceManager* pieceManager;
	
	//Load the game's textures
	LTexture gDotTexture;
	LTexture gDeadTexture;
	LTexture gBGTexture;
	LTexture gReadyTexture;
	LTexture gPowerTexture;

	LTexture rGhostTexture;
	LTexture bGhostTexture;
	LTexture pGhostTexture;
	LTexture yGhostTexture;
	LTexture evadeGhostTexture;

	LTexture bgTex;

	// Load music and sound effects
	Mix_Music *gSiren = NULL;
	Mix_Music *gIntro = NULL;
	Mix_Music *gEvade = NULL;
	Mix_Music *gDying = NULL;
	Mix_Chunk *gPellet0 = NULL;
	Mix_Chunk *gPellet1 = NULL;
	Mix_Chunk *eatGhost = NULL;
	
	void update(int frames);
	void render();
};