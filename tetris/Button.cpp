#include "Button.h"
#include "Game.h"

Button::Button(int x, int y, int _function)
{
	function = (Function)_function;
	rect = { x, y, 184, 78 };
	pressed = false;
}

Button::~Button()
{
	texture.free();
	fontTex.free();
}

void Button::loadMedia()
{
	texture.loadFromFile("media/button.png");
	std::string fontString;

	switch (function)
	{
	case ClearGrid:
		fontString = "clear grid";
		break;

	case ToggleGA:
		fontString = "toggle GA";
		break;

	case ToggleBlink:
		fontString = "row blink";
		break;

	case ToggleOnlyLines:
		fontString = "lines only";
		break;
	}

	SDL_Color fontColor = {0, 0, 0};
	fontTex.loadFromRenderedText(fontString, fontColor);
}

void Button::update()
{
	state = 0;
	int* x = new int;
	int* y = new int;
	
	SDL_GetMouseState(x, y);
	
	if (SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (*x >= rect.x && *x <= rect.x + rect.w &&
			*y >= rect.y && *y <= rect.y + rect.h)
		{
			if (!pressed && function != ClearGrid || function == ClearGrid)
			{
				doPress();
				pressed = true;
				state = 1;
				return;
			}
		}
	}
	else pressed = false;
}

void Button::doPress()
{
	switch (function)
	{
	case ClearGrid:
		Game::game()->clearGrid();
		break;

	case ToggleGA:
		Game::game()->toggleGA();
		break;

	case ToggleBlink:
		Game::game()->toggleBlinks();
		break;

	case ToggleOnlyLines:
		Game::game()->toggleOnlyLines();
		break;
	}
}

void Button::render()
{
	int drawY = -1;

	switch (function)
	{
	case ClearGrid:
		drawY = state*78;
		break;

	case ToggleGA:
		drawY = Game::game()->enableGA() ? abs(state-1)*78 : state*78;
		break;

	case ToggleBlink:
		drawY = Game::game()->doBlinks() ? abs(state-1)*78 : state*78;
		break;

	case ToggleOnlyLines:
		drawY = Game::game()->onlyLines() ? abs(state-1)*78 : state*78;
		break;
	}
	
	SDL_Rect clip = { 0, drawY, 184, 78 };
	texture.render(rect.x, rect.y, &clip);
	fontTex.render(rect.x+12, rect.y+10);
}