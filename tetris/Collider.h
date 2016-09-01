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
		SDL_Rect steve = { 0, 0, GRID_SIZE * 3, GRID_SIZE };
		SDL_Rect meme = { 0, GRID_SIZE, GRID_SIZE, GRID_SIZE };
		colliders.push_back(steve);
		colliders.push_back(meme);
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
};