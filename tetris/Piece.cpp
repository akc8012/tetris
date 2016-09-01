#include "Piece.h"

Piece::Piece(Shape s, Vector2<int> _pos)
	: shape(s), pos(_pos)
{
	switch (s)
	{
	case L:
		collider = new LCollider();
		break;

	case O:
		collider = new OCollider();
		break;
	}
}

void Piece::render()
{
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		SDL_Rect fillRect = { getCollider(i).x, getCollider(i).y, getCollider(i).w, getCollider(i).h };
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
		SDL_RenderFillRect(gRenderer, &fillRect);
	}
}

void Piece::fall(int frames)
{
	if (frames % 50 == 0)
		pos.y += GRID_SIZE;
}

SDL_Rect Piece::getCollider(int i)
{
	SDL_Rect rect = collider->get()[i];

	rect.x += pos.x;
	rect.y += pos.y;

	return rect;
}

void Piece::setColPoints()
{
	Grid grid;

	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		for (int w = 0; w < getCollider(i).w / GRID_SIZE; w++)
		{
			for (int h = 0; h < getCollider(i).h / GRID_SIZE; h++)
			{
				grid.setGrid(Vector2<int>(getCollider(i).x + (w*GRID_SIZE), getCollider(i).y + (h*GRID_SIZE)));
			}
		}
	}

	grid.printGrid();
}