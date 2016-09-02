#pragma once
#include "Piece.h"
#include "Grid.h"

class PieceManager
{
public:
	PieceManager(Grid* _grid);

	void loadMedia();
	void update(int frames);
	void spawnPiece();
	void render();

private:
	std::vector<Piece> pieces;
	int active;
	Grid* grid;
	Vector2<int> startPos;
	int dir;
	bool pressed;
	LTexture LTex;
	LTexture OTex;
};