#pragma once
#include "platform.h"

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Globally used font
extern TTF_Font *gFont;

extern bool enableGA;

enum Shape { I=1, J, L, O, S, T, Z };

// global screen size
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 576

// number of grid spaces horizontally and vertically
#define GRID_WIDTH 10
#define GRID_HEIGHT 18

#define GRID_SIZE 32
#define GRID_LENGTH 384		// x pixel length of grid

// globally defined directions
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3