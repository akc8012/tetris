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
			std::cout << "Pieces: " << deadPieces.size();

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
	//return new Piece(Piece::L, &LTex, grid);
}

void PieceManager::clearRow(int clearY)
{
	SDL_Rect clear = { 0, clearY, GRID_LENGTH, GRID_SIZE };
	SDL_Rect result;

	SDL_Rect* clip = new SDL_Rect { 0, 0, 64, 32 };
	
	for (Uint32 i = 0; i < deadPieces.size(); i++)
	{
		if (SDL_IntersectRect(&clear, &deadPieces[i].getRect(), &result))
		{
			if (result.w == deadPieces[i].getWidth() && result.h == deadPieces[i].getHeight())
			{
				deadPieces.erase(deadPieces.begin() + i--);
				continue;
			}

			int yDist = abs(clearY - deadPieces[i].getPos().y);

			if (yDist == 0 || yDist == deadPieces[i].getHeight() - 32)
			{
				SDL_Rect cover { deadPieces[i].getPos().x, deadPieces[i].getPos().y + yDist, deadPieces[i].getWidth(), 32 };
				deadPieces[i].pushCoverRect(cover);

				if (yDist == deadPieces[i].getHeight() - 32)
					deadPieces[i].moveDown();
			}
			else
			{
				/*DeadPiece newPiece = DeadPiece(deadPieces[i]);
				
				SDL_Rect botCover { deadPieces[i].getPos().x, deadPieces[i].getPos().y, deadPieces[i].getWidth(), yDist+32 };
				SDL_Rect topCover{ deadPieces[i].getPos().x, deadPieces[i].getPos().y+yDist, deadPieces[i].getWidth(), deadPieces[i].getHeight()-yDist };
				
				deadPieces[i].pushCoverRect(botCover);
				newPiece.pushCoverRect(topCover);
				deadPieces.push_back(newPiece);*/
			}
		}
	}

	std::cout << "Pieces: " << deadPieces.size();
}

void PieceManager::render()
{
	for (Uint32 i = 0; i < deadPieces.size(); i++)
		deadPieces[i].render();

	aPiece->render();
	nPiece->render();
}