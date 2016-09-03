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
		col = new ICollider(grid, &drawOff);
		break;

	case J:
		col = new JCollider(grid, &drawOff);
		break;

	case L:
		col = new LCollider(grid, &drawOff);
		break;

	case O:
		col = new OCollider(grid, &drawOff);
		break;

	case S:
		col = new SCollider(grid, &drawOff);
		break;

	case T:
		col = new TCollider(grid, &drawOff);
		break;

	case Z:
		col = new ZCollider(grid, &drawOff);
		break;
	}

	return col;
}

void Piece::render()
{
	for (Uint32 i = 0; i < collider->get().size(); i++)
	{
		SDL_Rect fillRect = { collider->calcPos(i, pos).x, collider->calcPos(i, pos).y, collider->get(i).w, collider->get(i).h };
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
		SDL_RenderFillRect(gRenderer, &fillRect);
	}

	texture->render(drawPos().x, drawPos().y, 0, drawRot());
}

bool Piece::fall()
{
	bool colliding = collider->checkColPoints(pos, &Vector2<int>(0, GRID_SIZE));

	if (!colliding)
		pos.y += GRID_SIZE;

	return colliding;
}

void Piece::move(int dir)
{
	bool colliding = collider->checkColPoints(pos, &Vector2<int>(dir*GRID_SIZE, 0));

	if (!colliding)
		pos.x += dir*GRID_SIZE;
}

void Piece::rotate(int dir)
{
	int oldRot = rotation;
	
	rotation += dir < 0 ? 3 : dir;
	rotation %= 4;
	collider->rotate(rotation, &drawOff);

	if (collider->checkColPoints(pos))
	{
		rotation = oldRot;
		collider->rotate(rotation, &drawOff);
	}
}