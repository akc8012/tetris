#include "PieceManager.h"

PieceManager::PieceManager(Grid* _grid) : grid(_grid)
{
	startPos = Vector2<int>(160, 0);

	spawnPiece();

	pressed = false;
}

PieceManager::~PieceManager()
{
	ITex.free();
	JTex.free();
	LTex.free();
	OTex.free();
	STex.free();
	TTex.free();
	ZTex.free();
}

void PieceManager::loadMedia()
{
	ITex.loadFromFile("media/ITex.png");
	JTex.loadFromFile("media/JTex.png");
	LTex.loadFromFile("media/LTex.png");
	OTex.loadFromFile("media/OTex.png");
	STex.loadFromFile("media/STex.png");
	TTex.loadFromFile("media/TTex.png");
	ZTex.loadFromFile("media/ZTex.png");
}

void PieceManager::update(int frames)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_RIGHT] != 0 && !pressed)
	{
		pieces[active].move(1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] != 0 && !pressed)
	{
		pieces[active].move(-1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_X] != 0 && !pressed)
	{
		pieces[active].rotate(1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_Z] != 0 && !pressed)
	{
		pieces[active].rotate(-1);
		pressed = true;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0 && currentKeyStates[SDL_SCANCODE_LEFT] == 0 &&
		currentKeyStates[SDL_SCANCODE_X] == 0 && currentKeyStates[SDL_SCANCODE_Z] == 0) pressed = false;

	if (frames % (currentKeyStates[SDL_SCANCODE_DOWN] != 0 ? 5 : 15) == 0)
	{
		if (pieces[active].fall())
		{
			pieces[active].setColPoints();

			DeadTexture dead;
			dead.texture = pieces[active].getTexture();
			dead.pos = pieces[active].drawPos();
			dead.rotation = pieces[active].drawRot();
			deadTextures.push_back(dead);

			pieces.erase(pieces.begin() + 0);

			spawnPiece();
		}
	}
}

void PieceManager::spawnPiece()
{
	Piece piece(Piece::L, &LTex, startPos, grid);
	//Piece piece2(Piece::O, Vector2<int>(128, 480), grid);

	pieces.push_back(piece);
	active = pieces.size() - 1;
	//pieces.push_back(piece2);
}

void PieceManager::render()
{
	for (Uint32 i = 0; i < pieces.size(); i++)
		pieces[i].render();

	for (Uint32 i = 0; i < deadTextures.size(); i++)
		deadTextures[i].render();
}