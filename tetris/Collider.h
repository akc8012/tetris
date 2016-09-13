#pragma once
#include "common.h"
#include "Vector2.h"
#include "Grid.h"
#include <vector>

class Collider
{
public:
	Collider(Grid* _grid) : grid(_grid), rotation(DOWN) { }

	std::vector<SDL_Rect> get() { return colliders; }
	SDL_Rect get(int i) { return colliders[i]; }

	Vector2<int> calcPos(int i, Vector2<int> pos);
	void setColPoints(Vector2<int> pos);
	bool checkColPoints(Vector2<int> pos, const Vector2<int>* posOffset = 0);

	virtual void rotate(int dir, Vector2<int>* drawOff = NULL) { }

protected:
	std::vector<SDL_Rect> colliders;
	Grid* grid;
	Shape shape;
	int rotation;
};

class ICollider : public Collider
{
public:
	ICollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = I;
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class JCollider : public Collider
{
public:
	JCollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = J;
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class LCollider : public Collider
{
public:
	LCollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = L;
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class OCollider : public Collider
{
public:
	OCollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = O;
		SDL_Rect meme = { GRID_SIZE, GRID_SIZE, GRID_SIZE * 2, GRID_SIZE * 2 };
		colliders.push_back(meme);
		*drawOff = Vector2<int>(32, 32);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL) { }
};

class SCollider : public Collider
{
public:
	SCollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = S;
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class TCollider : public Collider
{
public:
	TCollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = T;
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class ZCollider : public Collider
{
public:
	ZCollider(Grid* _grid, Vector2<int>* drawOff) : Collider(_grid)
	{
		shape = Z;
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};