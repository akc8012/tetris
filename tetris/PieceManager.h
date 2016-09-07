#pragma once
#include "Piece.h"

class PieceManager
{
public:
	PieceManager(Grid* _grid);
	~PieceManager();

	void loadMedia();
	void update(int frames);
	void render();
	void clearRow(int clearY);

private:
	
	Piece* spawnPiece();
	
	Piece* aPiece;
	Piece* nPiece;
	int active;
	Grid* grid;
	bool pressed;
	LTexture ITex;
	LTexture JTex;
	LTexture LTex;
	LTexture OTex;
	LTexture STex;
	LTexture TTex;
	LTexture ZTex;

	LTexture* textures[7] = { &ITex, &JTex, &LTex, &OTex, &STex, &TTex, &ZTex };

	std::vector<DeadPiece> deadPieces;
};