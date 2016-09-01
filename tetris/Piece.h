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

	Piece(Shape s, Vector2<int> _pos);

	void render();
	void fall(int frames);
	SDL_Rect getCollider(int i);
	void setColPoints();

private:
	Shape shape;
	Vector2<int> pos;
	Collider* collider;
};