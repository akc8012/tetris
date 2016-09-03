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
	SDL_Rect* clearRect;
	
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

	struct DeadPiece
	{
		LTexture* texture = 0;
		SDL_Rect* clip = 0;
		Collider* collider;
		Vector2<int> pos;
		int rotation;

		int getWidth()  { return rotation == 0 || rotation == 180 ? texture->getWidth() : texture->getHeight(); }
		int getHeight() { return rotation == 0 || rotation == 180 ? texture->getHeight() : texture->getWidth(); }

		void render() { texture->render(pos.x, pos.y, !clip ? 0 : clip, rotation); };
	};

	std::vector<DeadPiece> deadPieces;
};