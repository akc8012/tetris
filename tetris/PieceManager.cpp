#include "PieceManager.h"

PieceManager::PieceManager(Grid* _grid)
	: grid(_grid), pressed(false)
{
	srand((Uint32)time(NULL));

	nPiece = spawnPiece();
	aPiece = spawnPiece();
	aPiece->moveToStart();
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
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0 && currentKeyStates[SDL_SCANCODE_LEFT] == 0 &&
		currentKeyStates[SDL_SCANCODE_X] == 0 && currentKeyStates[SDL_SCANCODE_Z] == 0) pressed = false;

	if (frames % (currentKeyStates[SDL_SCANCODE_DOWN] != 0 ? 5 : 15) == 0)
	{
		if (aPiece->fall())
		{
			aPiece->setColPoints();

			DeadTexture dead;
			dead.texture = aPiece->getTexture();
			dead.pos = aPiece->drawPos();
			dead.rotation = aPiece->drawRot();
			deadTextures.push_back(dead);

			delete aPiece;
			aPiece = nPiece;
			nPiece = spawnPiece();
			aPiece->moveToStart();
		}
	}
}

Piece* PieceManager::spawnPiece()
{
	int r = rand() % 7;
	return new Piece((Piece::Shape)r, textures[r], grid);
}

void PieceManager::render()
{
	aPiece->render();
	nPiece->render();

	for (Uint32 i = 0; i < deadTextures.size(); i++)
		deadTextures[i].render();
}