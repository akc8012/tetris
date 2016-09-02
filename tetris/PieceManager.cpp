#include "PieceManager.h"

PieceManager::PieceManager(Grid* _grid) : grid(_grid)
{
	startPos = Vector2<int>(160, 0);

	spawnPiece();

	dir = DOWN;
	pressed = false;
	//pieces[1].setColPoints();
}

void PieceManager::loadMedia()
{
	LTex.loadFromFile("media/LTex.png");
	OTex.loadFromFile("media/OTex.png");
}

void PieceManager::update(int frames)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_RIGHT] != 0 && !pressed)
	{
		dir += 1;
		dir %= 4;
		pressed = true;
		pieces[active].rotate(dir);
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0) pressed = false;

	if (frames % 50 == 0)
	{
		if (pieces[active].active && pieces[active].fall())
		{
			pieces[active].setColPoints();
			//pieces.erase(pieces.begin() + 0);
			pieces[active].active = false;
			spawnPiece();
		}
	}
}

void PieceManager::spawnPiece()
{
	Piece piece(Piece::L, &LTex, startPos, grid);
	//Piece piece2(Piece::O, Vector2<int>(128, 480), grid);

	pieces.push_back(piece);
	active = pieces.size() - 1;
	//pieces.push_back(piece2);
}

void PieceManager::render()
{
	for (Uint32 i = 0; i < pieces.size(); i++)
		pieces[i].render();
}