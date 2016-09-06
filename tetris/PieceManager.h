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

	class DeadPiece
	{
	private:
		LTexture* texture = 0;
		Vector2<int> pos;
		int rotation = -1;

	public:
		
		int getHeight() { return rotation == 0 || rotation == 180 ? texture->getHeight() : texture->getWidth(); }
		int getWidth() { return rotation == 0 || rotation == 180 ? texture->getWidth() : texture->getHeight(); }
		
		void setTexture(LTexture* t) { texture = t; }
		void setRotation(int rot) { rotation = rot; }

		void setPos(Vector2<int> p)
		{
			switch (rotation)
			{
			case 90:
				p.x += (texture->getWidth() + texture->getHeight()) / 2; 
				p.y -= abs(texture->getWidth() - texture->getHeight()) / 2;
				break;

			case 180:
				p.x += texture->getWidth();
				p.y += texture->getHeight();
				break;

			case -90:
				p.x += abs(texture->getWidth() - texture->getHeight()) / 2;
				p.y += (texture->getWidth() + texture->getHeight()) / 2;
				break;
			}

			pos = p;
		}

		void render()
		{
			SDL_Point center = { 0, 0 };
			texture->render(pos.x, pos.y, 0, rotation, &center);
		};

	};

	std::vector<DeadPiece> deadPieces;
};