#pragma once
#include "Piece.h"
#include <vector>

class PieceManager
{
public:
	PieceManager()
	{
		Piece piece(Piece::L, Vector2<int>(128, 96));
		Piece piece2(Piece::O, Vector2<int>(96, 480));

		pieces.push_back(piece);
		pieces.push_back(piece2);

		pieces[0].setColPoints();
	}

	void update(int frames)
	{
		pieces[0].fall(frames);
	}

	void render()
	{
		for (Uint32 i = 0; i < pieces.size(); i++)
			pieces[i].render();
	}

private:
	std::vector<Piece> pieces;

};