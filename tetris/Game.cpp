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
	button0 = new Button(436, 22, 0);
	button1 = new Button(436, 110, 1);
	button2 = new Button(436, 198, 2);
	button3 = new Button(436, 286, 3);
}

bool Game::loadMedia()
{
	if (!bgTex.loadFromFile("media/background.png"))
		return false;

	gFont = TTF_OpenFont("fonts/PIXELADE.ttf", 46);

	grid->loadMedia();
	pieceManager->loadMedia();
	button0->loadMedia();
	button1->loadMedia();
	button2->loadMedia();
	button3->loadMedia();

	return true;
}

void Game::close()
{
	//Free loaded images
	bgTex.free();

	TTF_CloseFont(gFont);
	gFont = NULL;
	
	delete button3;
	delete button2;
	delete button1;
	delete button0;
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

void Game::clearGrid()
{
	grid->clearGrid();
}

void Game::update(int frames)
{	
	button1->update();
	button2->update();
	button3->update();
	
	if (grid->isBlinking() || grid->isFilling())
		return;

	button0->update();
	
	if (enableGAFlag)
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
}

void Game::render()
{
	bgTex.render(0, 0);
	grid->render();

	if (!grid->isFilling())
		pieceManager->render();

	button0->render();
	button1->render();
	button2->render();
	button3->render();
}