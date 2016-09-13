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

	delete pieceManager;
	delete grid;
	delete ga;
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
	ga->epoch();
	pieceManager->update(frames);
}

void Game::render()
{
	bgTex.render(0, 0);
	grid->render();
	pieceManager->render();
}