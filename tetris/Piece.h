#pragma once
#include "common.h"
#include "Vector2.h"
#include "Grid.h"
#include "Collider.h"
#include "LTexture.h"
#include <vector>

class Piece
{
public:

	enum Shape { I, J, L, O, S, T, Z };

	Piece(Shape s, LTexture* t, Grid* _grid);

	void render();
	void moveToStart();
	bool fall();
	void setColPoints() { collider->setColPoints(pos); }
	void move(int dir);
	void rotate(int dir);
	
	LTexture* getTexture() { return texture; }
	Vector2<int> getPos() { return pos; }
	Vector2<int> drawPos() { return Vector2<int>(pos.x + drawOff.x + rotOff[rotation].x, pos.y + drawOff.y + rotOff[rotation].y); }
	int drawRot() { return ((rotation - 1) % 4) * 90; }

private:

	Collider* createCollider(Shape s);
	
	Shape shape;
	Vector2<int> pos;
	Vector2<int> drawOff;
	Collider* collider;
	Grid* grid;
	LTexture* texture;
	int rotation;
	Vector2<int> rotOff[4] = { Vector2<int>(0, -1), Vector2<int>(0, 0), Vector2<int>(-1, 0), Vector2<int>(-1, -1) };
};

class DeadPiece
{
private:
	LTexture* texture;
	Vector2<int> pos;
	Vector2<int> drawPos;
	SDL_Rect rect;
	std::vector<SDL_Rect> coverRects;
	int rotation;
	int distDown;

public:

	DeadPiece() : texture(0), rotation(-1) { }

	int getHeight() { return rotation == 0 || rotation == 180 ? texture->getHeight()-distDown : texture->getWidth()-distDown; }
	int getWidth() { return rotation == 0 || rotation == 180 ? texture->getWidth() : texture->getHeight(); }

	void setTexture(LTexture* t) { texture = t; }
	void setRotation(int rot) { rotation = rot; }
	Vector2<int> getPos() { return pos; }
	SDL_Rect getRect() { return rect; }
	void pushCoverRect(SDL_Rect c) { coverRects.push_back(c); };

	void setRect()
	{
		rect.x = pos.x;
		rect.y = pos.y;
		rect.w = getWidth();
		rect.h = getHeight();
	}

	void setPos(Vector2<int> p)
	{
		switch (rotation)
		{
		case 0:
			pos = p;
			break;

		case 90:
			p.x += (texture->getWidth() + texture->getHeight()) / 2;
			p.y -= abs(texture->getWidth() - texture->getHeight()) / 2;
			pos.x = p.x - getWidth() + 1;
			pos.y = p.y;
			break;

		case 180:
			p.x += texture->getWidth();
			p.y += texture->getHeight();
			pos.x = p.x - getWidth() + 1;
			pos.y = p.y - getHeight() + 1;
			break;

		case -90:
			p.x += abs(texture->getWidth() - texture->getHeight()) / 2;
			p.y += (texture->getWidth() + texture->getHeight()) / 2;
			pos.x = p.x;
			pos.y = p.y - getHeight() + 1;
			break;
		}

		drawPos = p;
		setRect();
	}

	void moveDown()
	{
		distDown += GRID_SIZE;
		pos.y += GRID_SIZE;
		drawPos.y += GRID_SIZE;

		for (Uint32 i = 0; i < coverRects.size(); i++)
			coverRects[i].y += GRID_SIZE;

		setRect();
	}

	void render()
	{
		SDL_Point center { 0, 0 };
		texture->render(drawPos.x, drawPos.y, 0, rotation, &center);

		for (Uint32 i = 0; i < coverRects.size(); i++)
		{
			SDL_SetRenderDrawColor(gRenderer, 248, 248, 248, 255);
			SDL_RenderFillRect(gRenderer, &coverRects[i]);
		}
	};

};