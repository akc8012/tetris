#include "PieceManager.h"
#include <bitset>

PieceManager::PieceManager(Grid* _grid)
	: grid(_grid), pressed(false), doFall(true)
{
	nPiece = spawnPiece();
	aPiece = spawnPiece();
	aPiece->moveToStart();

	tPiece = new Piece(aPiece->getShape(), textures[(int)aPiece->getShape()-1], grid);
	tPiece->moveToStart();
}

PieceManager::~PieceManager()
{
	ITex.free();
	JTex.free();
	LTex.free();
	OTex.free();
	STex.free();
	TTex.free();
	ZTex.free();

	delete aPiece;
	delete nPiece;
	delete tPiece;
}

void PieceManager::loadMedia()
{
	ITex.loadFromFile("media/ITex.png");
	JTex.loadFromFile("media/JTex.png");
	LTex.loadFromFile("media/LTex.png");
	OTex.loadFromFile("media/OTex.png");
	STex.loadFromFile("media/STex.png");
	TTex.loadFromFile("media/TTex.png");
	ZTex.loadFromFile("media/ZTex.png");
}

void PieceManager::update(int frames)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_RIGHT] != 0 && !pressed)
	{
		aPiece->move(1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] != 0 && !pressed)
	{
		aPiece->move(-1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_X] != 0 && !pressed)
	{
		aPiece->rotate(1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_Z] != 0 && !pressed)
	{
		aPiece->rotate(-1);
		pressed = true;
		//doFall = !doFall;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0 && currentKeyStates[SDL_SCANCODE_LEFT] == 0 &&
		currentKeyStates[SDL_SCANCODE_X] == 0 && currentKeyStates[SDL_SCANCODE_Z] == 0) pressed = false;

	if (frames % (currentKeyStates[SDL_SCANCODE_DOWN] != 0 ? 5 : 15) == 0 && doFall)
	{
		if (aPiece->fall())
		{
			setPiece();
		}
	}
}

int PieceManager::moveByChromo(int move, int rot, bool set)
{
	tPiece->moveToStart();
	
	if (move < 8)
	{
		for (int i = 0; i < move; i++)
			tPiece->move(-1);
	}
	else
	{
		for (int i = 0; i < move - 8; i++)
			tPiece->move(1);
	}

	if (rot < 4)
	{
		for (int i = 0; i < rot; i++)
			tPiece->rotate(-1);
	}
	else
	{
		for (int i = 0; i < rot - 4; i++)
			tPiece->rotate(1);
	}

	tPiece->land();
	int fitness = tPiece->getFitness();

	if (set)
	{
		delete aPiece;
		aPiece = tPiece;
		setPiece();
	}

	return fitness;
}

void PieceManager::setPiece()
{
	aPiece->setColPoints();

	delete aPiece;
	aPiece = nPiece;
	nPiece = spawnPiece();
	aPiece->moveToStart();

	tPiece = new Piece(aPiece->getShape(), textures[(int)aPiece->getShape() - 1], grid);
	tPiece->moveToStart();
}

Piece* PieceManager::spawnPiece()
{
	//int r = rand() % 7;
	//return new Piece((Shape)(r+1), textures[r], grid);
	return new Piece(L, &LTex, grid);
}

void PieceManager::render()
{
	aPiece->render();
	nPiece->render();
	tPiece->render();
}