#pragma once
#include "common.h"
#include "Vector2.h"
#include <vector>

class Collider
{
public:
	Collider() { }

	std::vector<SDL_Rect> get()
	{
		return colliders;
	}

	virtual void rotate(int dir) { }

protected:
	std::vector<SDL_Rect> colliders;
};

class LCollider : public Collider
{
public:
	LCollider()
	{
		rotate(DOWN);
	}

	void rotate(int dir)
	{
		colliders.clear();

		SDL_Rect rect0;
		SDL_Rect rect1;
		
		switch (dir)
		{
		case RIGHT:
			rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
			rect1 = { GRID_SIZE * 2, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE };
			colliders.push_back(rect0);
			colliders.push_back(rect1);
			break;

		case DOWN:
			rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
			rect1 = { 0, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE };
			colliders.push_back(rect0);
			colliders.push_back(rect1);
			break;

		case LEFT:
			rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
			rect1 = { 0, 0, GRID_SIZE, GRID_SIZE };
			colliders.push_back(rect0);
			colliders.push_back(rect1);
			break;

		case UP:
			rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
			rect1 = { GRID_SIZE * 2, 0, GRID_SIZE, GRID_SIZE };
			colliders.push_back(rect0);
			colliders.push_back(rect1);
			break;
		}
	}
};

class OCollider : public Collider
{
public:
	OCollider()
	{
		SDL_Rect meme = { 0, 0, GRID_SIZE * 2, GRID_SIZE * 2 };
		colliders.push_back(meme);
	}

	void rotate(int dir) { }
};