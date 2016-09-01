#pragma once
#include "common.h"
#include "Vector2.h"
#include "Grid.h"
#include "Collider.h"
#include <vector>

class Piece
{
public:

	enum Shape { I, O, T, S, Z, J, L };

	Piece(Shape s, Vector2<int> _pos, Grid* _grid);

	void render();
	void fall();
	SDL_Rect getCollider(int i);
	void setColPoints();
	bool checkColPoints(int yOffset = 0);
	void rotate(int dir) { collider->rotate(dir); };

private:
	Shape shape;
	Vector2<int> pos;
	Collider* collider;
	Grid* grid;
};