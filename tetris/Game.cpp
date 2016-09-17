#include "Game.h"

Game::Game()
{
	srand((Uint32)time(NULL));
}

Game::~Game()
{
	
}

void Game::init()
{
	grid = new Grid();
	pieceManager = new PieceManager(grid);
	ga = new GA(pieceManager);
}

bool Game::loadMedia()
{
	if (!bgTex.loadFromFile("media/background.png"))
		return false;

	grid->loadMedia();
	pieceManager->loadMedia();

	return true;
}

void Game::close()
{
	//Free loaded images
	bgTex.free();
	
	delete ga;
	delete pieceManager;
	delete grid;
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

void Game::clearRow(int clearY)
{
	
}

void Game::update(int frames)
{
	if (enableGA)
	{
		gaTicks++;

		if (gaTicks < 20)
			ga->epoch();
		else
		{
			ga->finish();
			gaTicks = 0;
		}
	}

	pieceManager->update(frames);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_C] != 0)
	{
		grid->clearGrid();
	}
}

void Game::render()
{
	bgTex.render(0, 0);
	grid->render();
	pieceManager->render();
}