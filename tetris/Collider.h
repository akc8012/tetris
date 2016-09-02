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

	virtual void rotate(int dir, Vector2<int>* drawOff = NULL) { }

protected:
	std::vector<SDL_Rect> colliders;
};

class LCollider : public Collider
{
public:
	LCollider(Vector2<int>* drawOff)
	{
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class OCollider : public Collider
{
public:
	OCollider(Vector2<int>* drawOff)
	{
		SDL_Rect meme = { GRID_SIZE, GRID_SIZE, GRID_SIZE * 2, GRID_SIZE * 2 };
		colliders.push_back(meme);
		*drawOff = Vector2<int>(32, 32);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL) { }
};