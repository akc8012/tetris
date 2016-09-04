#include "Collider.h"

Vector2<int> Collider::calcPos(int i, Vector2<int> pos)
{
	Vector2<int> colPos;

	colPos.x = colliders[i].x + pos.x;
	colPos.y = colliders[i].y + pos.y;

	return colPos;
}

void Collider::setColPoints(Vector2<int> pos)
{
	for (Uint32 i = 0; i < colliders.size(); i++)
	{
		for (int w = 0; w < colliders[i].w / GRID_SIZE; w++)
		{
			for (int h = 0; h < colliders[i].h / GRID_SIZE; h++)
			{
				grid->setGrid(Vector2<int>(calcPos(i, pos).x + (w*GRID_SIZE), calcPos(i, pos).y + (h*GRID_SIZE)));
			}
		}
	}

	grid->printGrid();
}

bool Collider::checkColPoints(Vector2<int> pos, const Vector2<int>* posOffset)
{
	if (posOffset == NULL) posOffset = new Vector2<int>(0, 0);
	
	for (Uint32 i = 0; i < colliders.size(); i++)
	{
		for (int w = 0; w < colliders[i].w / GRID_SIZE; w++)
		{
			for (int h = 0; h < colliders[i].h / GRID_SIZE; h++)
			{
				Vector2<int> checkPoint = Vector2<int>(calcPos(i, pos).x + (w*GRID_SIZE) + posOffset->x,
					calcPos(i, pos).y + (h*GRID_SIZE) + posOffset->y);

				if (grid->checkGrid(checkPoint))
					return true;
			}
		}
	}

	return false;
}

bool Collider::checkAgainstRow(int row, Vector2<int> pos)
{
	for (Uint32 i = 0; i < colliders.size(); i++)
	{
		for (int w = 0; w < colliders[i].w / GRID_SIZE; w++)
		{
			for (int h = 0; h < colliders[i].h / GRID_SIZE; h++)
			{
				if ((calcPos(i, pos).y + (h*GRID_SIZE)) / GRID_SIZE == row)
					return true;
			}
		}
	}

	return false;
}

void ICollider::rotate(int dir, Vector2<int>* drawOff)
{
	colliders.clear();

	SDL_Rect rect;

	switch (dir)
	{
	case RIGHT:
		rect = { GRID_SIZE * 2, 0, GRID_SIZE, GRID_SIZE * 4 };
		colliders.push_back(rect);
		if (drawOff) *drawOff = Vector2<int>(16, 48);
		break;

	case DOWN:
		rect = { 0, GRID_SIZE * 2, GRID_SIZE * 4, GRID_SIZE };
		colliders.push_back(rect);
		if (drawOff) *drawOff = Vector2<int>(0, 64);
		break;

	case LEFT:
		rect = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 4 };
		colliders.push_back(rect);
		if (drawOff) *drawOff = Vector2<int>(-16, 48);
		break;

	case UP:
		rect = { 0, GRID_SIZE, GRID_SIZE * 4, GRID_SIZE };
		colliders.push_back(rect);
		if (drawOff) *drawOff = Vector2<int>(0, 32);
		break;
	}
}

void JCollider::rotate(int dir, Vector2<int>* drawOff)
{
	colliders.clear();

	SDL_Rect rect0;
	SDL_Rect rect1;

	switch (dir)
	{
	case RIGHT:
		rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
		rect1 = { GRID_SIZE * 2, 0, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(16, 16);
		break;

	case DOWN:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
		rect1 = { GRID_SIZE * 2, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 32);
		break;

	case LEFT:
		rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
		rect1 = { 0, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(-16, 16);
		break;

	case UP:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
		rect1 = { 0, 0, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 0);
		break;
	}
}

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

void SCollider::rotate(int dir, Vector2<int>* drawOff)
{
	colliders.clear();

	SDL_Rect rect0;
	SDL_Rect rect1;

	switch (dir)
	{
	case RIGHT:
		rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 2 };
		rect1 = { GRID_SIZE * 2, GRID_SIZE, GRID_SIZE, GRID_SIZE * 2 };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(16, 16);
		break;

	case DOWN:
		rect0 = { GRID_SIZE, GRID_SIZE, GRID_SIZE * 2, GRID_SIZE };
		rect1 = { 0, GRID_SIZE * 2, GRID_SIZE * 2, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 32);
		break;

	case LEFT:
		rect0 = { 0, 0, GRID_SIZE, GRID_SIZE * 2 };
		rect1 = { GRID_SIZE, GRID_SIZE, GRID_SIZE, GRID_SIZE * 2 };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(-16, 16);
		break;

	case UP:
		rect0 = { GRID_SIZE, 0, GRID_SIZE * 2, GRID_SIZE };
		rect1 = { 0, GRID_SIZE, GRID_SIZE * 2, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 0);
		break;
	}
}

void TCollider::rotate(int dir, Vector2<int>* drawOff)
{
	colliders.clear();

	SDL_Rect rect0;
	SDL_Rect rect1;

	switch (dir)
	{
	case RIGHT:
		rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
		rect1 = { GRID_SIZE * 2, GRID_SIZE, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(16, 16);
		break;

	case DOWN:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
		rect1 = { GRID_SIZE, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 32);
		break;

	case LEFT:
		rect0 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 3 };
		rect1 = { 0, GRID_SIZE, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(-16, 16);
		break;

	case UP:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 3, GRID_SIZE };
		rect1 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 0);
		break;
	}
}

void ZCollider::rotate(int dir, Vector2<int>* drawOff)
{
	colliders.clear();

	SDL_Rect rect0;
	SDL_Rect rect1;

	switch (dir)
	{
	case RIGHT:
		rect0 = { GRID_SIZE, GRID_SIZE, GRID_SIZE, GRID_SIZE * 2 };
		rect1 = { GRID_SIZE * 2, 0, GRID_SIZE, GRID_SIZE * 2 };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(16, 16);
		break;

	case DOWN:
		rect0 = { 0, GRID_SIZE, GRID_SIZE * 2, GRID_SIZE };
		rect1 = { GRID_SIZE, GRID_SIZE * 2, GRID_SIZE * 2, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 32);
		break;

	case LEFT:
		rect0 = { 0, GRID_SIZE, GRID_SIZE, GRID_SIZE * 2 };
		rect1 = { GRID_SIZE, 0, GRID_SIZE, GRID_SIZE * 2 };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(-16, 16);
		break;

	case UP:
		rect0 = { 0, 0, GRID_SIZE * 2, GRID_SIZE };
		rect1 = { GRID_SIZE, GRID_SIZE, GRID_SIZE * 2, GRID_SIZE };
		colliders.push_back(rect0);
		colliders.push_back(rect1);
		if (drawOff) *drawOff = Vector2<int>(0, 0);
		break;
	}
}