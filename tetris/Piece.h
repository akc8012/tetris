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

	enum Shape { I, O, T, S, Z, J, L };

	Piece(Shape s, LTexture* t, Vector2<int> _pos, Grid* _grid);

	void render();
	bool fall();
	SDL_Rect getCollider(int i);
	void setColPoints();
	bool checkColPoints(int yOffset = 0);
	void rotate(int dir);
	bool active;

private:
	Shape shape;
	Vector2<int> pos;
	Vector2<int> drawOff;
	Collider* collider;
	Grid* grid;
	LTexture* texture;
	int rotation;
	Vector2<int> rotOff[4] = { Vector2<int>(0, -1), Vector2<int>(0, 0), Vector2<int>(-1, 0), Vector2<int>(-1, -1) };
};