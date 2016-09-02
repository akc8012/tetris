#include "Piece.h"

Piece::Piece(Shape s, LTexture* t, Vector2<int> _pos, Grid* _grid)
	: texture(t), shape(s), pos(_pos), grid(_grid)
{
	active = true;
	rotation = DOWN;
	
	switch (s)
	{
	case L:
		collider = new LCollider(&drawOff);
		break;

	case O:
		collider = new OCollider(&drawOff);
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

	if (texture != NULL)
		texture->render(pos.x+drawOff.x+rotOff[rotation].x, pos.y+drawOff.y+rotOff[rotation].y, 0, ((rotation-1)%4)*90);
}

bool Piece::fall()
{
	bool colliding = checkColPoints(GRID_SIZE);

	if (!colliding)
		pos.y += GRID_SIZE;

	return colliding;
}

void Piece::rotate(int dir)
{
	rotation = dir;
	collider->rotate(dir, &drawOff);
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
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		for (int w = 0; w < getCollider(i).w / GRID_SIZE; w++)
		{
			for (int h = 0; h < getCollider(i).h / GRID_SIZE; h++)
			{
				grid->setGrid(Vector2<int>(getCollider(i).x + (w*GRID_SIZE), getCollider(i).y + (h*GRID_SIZE)));
			}
		}
	}

	grid->printGrid();
}

bool Piece::checkColPoints(int yOffset)
{
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		for (int w = 0; w < getCollider(i).w / GRID_SIZE; w++)
		{
			for (int h = 0; h < getCollider(i).h / GRID_SIZE; h++)
			{
				if (grid->checkGrid(Vector2<int>(getCollider(i).x + (w*GRID_SIZE), getCollider(i).y + (h*GRID_SIZE) + yOffset)))
					return true;
			}
		}
	}

	return false;
}