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

	SDL_Rect get(int i)
	{
		return colliders[i];
	}

	virtual void rotate(int dir, Vector2<int>* drawOff = NULL) { }

protected:
	std::vector<SDL_Rect> colliders;
};

class ICollider : public Collider
{
public:
	ICollider(Vector2<int>* drawOff)
	{
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class JCollider : public Collider
{
public:
	JCollider(Vector2<int>* drawOff)
	{
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
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

class SCollider : public Collider
{
public:
	SCollider(Vector2<int>* drawOff)
	{
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class TCollider : public Collider
{
public:
	TCollider(Vector2<int>* drawOff)
	{
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};

class ZCollider : public Collider
{
public:
	ZCollider(Vector2<int>* drawOff)
	{
		rotate(DOWN, drawOff);
	}

	void rotate(int dir, Vector2<int>* drawOff = NULL);
};