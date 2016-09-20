#pragma once
#include "common.h"
#include "LTexture.h"
#include "Vector2.h"

class Button
{
private:
	SDL_Rect rect;
	LTexture texture;
	LTexture fontTex;
	enum Function { ClearGrid, ToggleGA, ToggleBlink, ToggleOnlyLines };
	Function function;
	int state;
	bool pressed;

public:
	Button(int x, int y, int _function);
	~Button();

	void loadMedia();
	void update();
	void doPress();
	void render();
};