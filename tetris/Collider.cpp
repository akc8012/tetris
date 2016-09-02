#include "Collider.h"

void LCollider::rotate(int dir, Vector2<int>* drawOff)
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
		if (drawOff) *drawOff = Vector2<int>(16, 16);
		break;

	case DOWN:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
		rect1 = { 0, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 32);
		break;

	case LEFT:
		rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
		rect1 = { 0, 0, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(-16, 16);
		break;

	case UP:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
		rect1 = { GRID_SIZE * 2, 0, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 0);
		break;
	}
}