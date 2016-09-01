#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{
	
}

bool Game::loadMedia()
{
	if (!gDotTexture.loadFromFile("media/pacSheet.png"))
		return false;
	if (!gDeadTexture.loadFromFile("media/deadSheet.png"))
		return false;
	if (!gBGTexture.loadFromFile("media/playfield.png"))
		return false;
	if (!gReadyTexture.loadFromFile("media/ready.png"))
		return false;
	if (!gPowerTexture.loadFromFile("media/powerPellet.png"))
		return false;
	if (!rGhostTexture.loadFromFile("media/redGhost.png"))
		return false;
	if (!bGhostTexture.loadFromFile("media/blueGhost.png"))
		return false;
	if (!pGhostTexture.loadFromFile("media/pinkGhost.png"))
		return false;
	if (!yGhostTexture.loadFromFile("media/yellowGhost.png"))
		return false;
	if (!evadeGhostTexture.loadFromFile("media/evadeGhost.png"))
		return false;

	if (!bgTex.loadFromFile("media/background.png"))
		return false;

	gIntro = Mix_LoadMUS("audio/intro.wav");
	if (gIntro == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	gSiren = Mix_LoadMUS("audio/siren.wav");
	if (gSiren == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	gEvade = Mix_LoadMUS("audio/evade.wav");
	if (gSiren == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	gDying = Mix_LoadMUS("audio/dying.wav");
	if (gSiren == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	gPellet0 = Mix_LoadWAV("audio/pellet0.wav");
	if (gPellet0 == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	gPellet1 = Mix_LoadWAV("audio/pellet1.wav");
	if (gPellet1 == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	eatGhost = Mix_LoadWAV("audio/eatGhost.wav");
	if (gPellet1 == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

void Game::init()
{
	grid = new Grid();
	pieceManager = new PieceManager(grid);
}

void Game::close()
{
	//Free loaded images
	rGhostTexture.free();
	evadeGhostTexture.free();
	bGhostTexture.free();
	pGhostTexture.free();
	yGhostTexture.free();
	gPowerTexture.free();
	gReadyTexture.free();
	gBGTexture.free();
	gDotTexture.free();
	gDeadTexture.free();
	bgTex.free();

	//Free sounds
	Mix_FreeChunk(gPellet0);
	Mix_FreeChunk(gPellet1);
	Mix_FreeChunk(eatGhost);
	gPellet0 = NULL;
	gPellet1 = NULL;
	Mix_FreeMusic(gSiren);
	Mix_FreeMusic(gIntro);
	Mix_FreeMusic(gDying);
	Mix_FreeMusic(gEvade);
	gSiren = NULL;
	gDying = NULL;
	gIntro = NULL;
	gEvade = NULL;

	delete sGame;
}

void Game::run()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	// frame counter
	int frames = 0;

	// create all of the game objects

	while (!quit)	//While application is running
	{
		frames++;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// quit game
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
		}

		//update all objects
		update(frames);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render objects
		render();

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
}

void Game::update(int frames)
{
	pieceManager->update(frames);
}

void Game::render()
{
	bgTex.render(0, 0);
	pieceManager->render();
}