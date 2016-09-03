#include "Piece.h"

Piece::Piece(Shape s, LTexture* t, Vector2<int> _pos, Grid* _grid)
	: texture(t), shape(s), pos(_pos), grid(_grid)
{
	rotation = DOWN;
	
	switch (s)
	{
	case I:
		collider = new ICollider(&drawOff);
		break;

	case J:
		collider = new JCollider(&drawOff);
		break;

	case L:
		collider = new LCollider(&drawOff);
		break;

	case O:
		collider = new OCollider(&drawOff);
		break;

	case S:
		collider = new SCollider(&drawOff);
		break;

	case T:
		collider = new TCollider(&drawOff);
		break;

	case Z:
		collider = new ZCollider(&drawOff);
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

	texture->render(drawPos().x, drawPos().y, 0, drawRot());
}

bool Piece::fall()
{
	bool colliding = checkColPoints(GRID_SIZE);

	if (!colliding)
		pos.y += GRID_SIZE;

	return colliding;
}

void Piece::move(int dir)
{
	pos.x += dir*GRID_SIZE;
}

void Piece::rotate(int dir)
{
	rotation += dir < 0 ? 3 : dir;
	rotation %= 4;
	collider->rotate(rotation, &drawOff);
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