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

	Piece(Shape s, LTexture* t, Grid* _grid);

	void render();
	void moveToStart();
	bool fall();
	void land();
	void setColPoints() { collider->setColPoints(pos); }
	int getFitness() { return collider->setTempGetFitness(pos); }
	void move(int dir);
	void setPos(Vector2<int> _pos);
	void rotate(int dir);
	
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