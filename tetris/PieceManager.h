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
	int moveByChromo(int move, int rot, bool set);
	bool onlyLines() { return onlyLinesFlag; }
	void toggleOnlyLines() { onlyLinesFlag = !onlyLinesFlag; }

private:
	
	Piece* spawnPiece();
	void setPiece();
	bool onlyLinesFlag;
	
	Piece* aPiece;
	Piece* nPiece;
	Piece* tPiece;
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
};