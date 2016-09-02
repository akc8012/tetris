#pragma once
#include "Piece.h"

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
	bool pressed;
	LTexture LTex;
	LTexture OTex;

	struct DeadTexture
	{
		LTexture* texture = 0;
		SDL_Rect* clip = 0;
		Vector2<int> pos;
		int rotation;

		void render() { texture->render(pos.x, pos.y, !clip ? 0 : clip, rotation); };
	};

	std::vector<DeadTexture> deadTextures;
};