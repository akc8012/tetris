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

	struct DeadPiece
	{
		LTexture* texture = 0;
		std::vector<SDL_Rect> coverRects;
		Collider* collider = 0;
		Vector2<int> pos;
		Vector2<int> drawPos;
		int rotation;

		void render()
		{
			texture->render(drawPos.x, drawPos.y, 0, rotation);

			for (Uint32 i = 0; i < coverRects.size(); i++)
			{
				SDL_SetRenderDrawColor(gRenderer, 248, 248, 248, 255);
				SDL_RenderFillRect(gRenderer, &coverRects[i]);
			}
		};
	};

	std::vector<DeadPiece> deadPieces;
};