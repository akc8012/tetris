#pragma once
#include "Piece.h"
#include "Grid.h"
#include <vector>

class PieceManager
{
public:
	PieceManager(Grid* grid)
	{
		Piece piece(Piece::L, Vector2<int>(96, 96), grid);
		Piece piece2(Piece::O, Vector2<int>(128, 512), grid);

		pieces.push_back(piece);
		pieces.push_back(piece2);

		dir = 0;
		pressed = false;
		pieces[1].setColPoints();
	}

	void update(int frames)
	{
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_RIGHT] != 0 && !pressed)
		{
			dir += 1;
			dir %= 4;
			pressed = true;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0) pressed = false;

		pieces[0].rotate(dir);

		if (frames % 50 == 0)
			pieces[0].fall();
	}

	void render()
	{
		for (Uint32 i = 0; i < pieces.size(); i++)
			pieces[i].render();
	}

private:
	std::vector<Piece> pieces;
	int dir;
	bool pressed;
};