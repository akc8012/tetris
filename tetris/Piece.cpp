#include "Piece.h"

Piece::Piece(Shape s, LTexture* t, Vector2<int> _pos, Grid* _grid)
	: texture(t), shape(s), pos(_pos), grid(_grid)
{
	rotation = DOWN;
	
	collider = createCollider(s);
}

Collider* Piece::createCollider(Shape s)
{
	Collider* col = 0;
	
	switch (s)
	{
	case I:
		col = new ICollider(&drawOff);
		break;

	case J:
		col = new JCollider(&drawOff);
		break;

	case L:
		col = new LCollider(&drawOff);
		break;

	case O:
		col = new OCollider(&drawOff);
		break;

	case S:
		col = new SCollider(&drawOff);
		break;

	case T:
		col = new TCollider(&drawOff);
		break;

	case Z:
		col = new ZCollider(&drawOff);
		break;
	}

	return col;
}

void Piece::render()
{
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		SDL_Rect fillRect = { calcColPos(i).x, calcColPos(i).y, collider->get(i).w, collider->get(i).h };
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
		SDL_RenderFillRect(gRenderer, &fillRect);
	}

	texture->render(drawPos().x, drawPos().y, 0, drawRot());
}

bool Piece::fall()
{
	bool colliding = checkColPoints(&Vector2<int>(0, GRID_SIZE));

	if (!colliding)
		pos.y += GRID_SIZE;

	return colliding;
}

void Piece::move(int dir)
{
	bool colliding = checkColPoints(&Vector2<int>(dir*GRID_SIZE, 0));

	if (!colliding)
		pos.x += dir*GRID_SIZE;
}

void Piece::rotate(int dir)
{
	rotation += dir < 0 ? 3 : dir;
	rotation %= 4;
	collider->rotate(rotation, &drawOff);
}

Vector2<int> Piece::calcColPos(int i)
{
	Vector2<int> colPos;
	SDL_Rect rect = collider->get(i);

	colPos.x = rect.x += pos.x;
	colPos.y = rect.y += pos.y;

	return colPos;
}

void Piece::setColPoints()
{
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		for (int w = 0; w < collider->get(i).w / GRID_SIZE; w++)
		{
			for (int h = 0; h < collider->get(i).h / GRID_SIZE; h++)
			{
				grid->setGrid(Vector2<int>(calcColPos(i).x + (w*GRID_SIZE), calcColPos(i).y + (h*GRID_SIZE)));
			}
		}
	}

	grid->printGrid();
}

bool Piece::checkColPoints(const Vector2<int>* posOffset)
{
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		for (int w = 0; w < collider->get(i).w / GRID_SIZE; w++)
		{
			for (int h = 0; h < collider->get(i).h / GRID_SIZE; h++)
			{
				Vector2<int> checkPoint = Vector2<int>(calcColPos(i).x + (w*GRID_SIZE) + posOffset->x,
					calcColPos(i).y + (h*GRID_SIZE) + posOffset->y);
				
				if (grid->checkGrid(checkPoint))
					return true;
			}
		}
	}

	return false;
}