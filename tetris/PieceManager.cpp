#include "PieceManager.h"

PieceManager::PieceManager(Grid* _grid)
	: grid(_grid), pressed(false)
{
	srand((Uint32)time(NULL));

	nPiece = spawnPiece();
	aPiece = spawnPiece();
	aPiece->moveToStart();

	clearRect = new SDL_Rect{0, 0, 1, 1};
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

			DeadPiece dead;
			dead.texture = aPiece->getTexture();
			dead.pos = aPiece->drawPos();
			dead.rotation = aPiece->drawRot();

			deadPieces.push_back(dead);

			delete aPiece;
			aPiece = nPiece;
			nPiece = spawnPiece();
			aPiece->moveToStart();
		}
	}
}

Piece* PieceManager::spawnPiece()
{
	//int r = rand() % 7;
	//return new Piece((Piece::Shape)r, textures[r], grid);
	return new Piece(Piece::I, &ITex, grid);
}

void PieceManager::clearRow(int clearY)
{
	clearRect = new SDL_Rect{ 0, clearY, SCREEN_WIDTH, GRID_SIZE };
	
	/*for (Uint32 i = 0; i < deadTexs.size(); i++)
	{
		SDL_Rect texRect = { deadTexs[i].pos.x, deadTexs[i].pos.y, deadTexs[i].getWidth(), deadTexs[i].getHeight() };
		SDL_Rect resultRect;
		
		if (SDL_IntersectRect(clearRect, &texRect, &resultRect))
		{
			deadTexs[i].texture = &TTex;
		}
	}*/
}

void PieceManager::render()
{
	aPiece->render();
	nPiece->render();

	for (Uint32 i = 0; i < deadPieces.size(); i++)
		deadPieces[i].render();

	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 128);
	SDL_RenderFillRect(gRenderer, clearRect);
}