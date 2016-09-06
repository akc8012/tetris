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

			DeadPiece dead;
			dead.setTexture(aPiece->getTexture());
			dead.setRotation(aPiece->drawRot());
			dead.setPos(aPiece->drawPos());

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
	int r = rand() % 7;
	return new Piece((Piece::Shape)r, textures[r], grid);
	//return new Piece(Piece::I, &ITex, grid);
}

void PieceManager::clearRow(int clearY)
{
	for (Uint32 i = 0; i < deadPieces.size(); i++)
	{
		/*std::vector<Vector2<int>> covers = deadPieces[i].collider->checkAgainstRow(clearY, deadPieces[i].pos);
		
		for (Uint32 j = 0; j < covers.size(); j++)
		{
			SDL_Rect cover = { covers[j].x, covers[j].y, 32, 32 };
			deadPieces[i].coverRects.push_back(cover);
		}*/

		//deadPieces[i].pos.y += GRID_SIZE;
		//deadPieces[i].drawPos.y += GRID_SIZE;
	}
}

void PieceManager::render()
{
	for (Uint32 i = 0; i < deadPieces.size(); i++)
		deadPieces[i].render();

	aPiece->render();
	nPiece->render();
}