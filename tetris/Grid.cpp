#include "Grid.h"
#include "Game.h"

Grid::Grid()
{

}

Grid::~Grid()
{
	IBlockTex.free();
	JBlockTex.free();
	LBlockTex.free();
	OBlockTex.free();
	SBlockTex.free();
	TBlockTex.free();
	ZBlockTex.free();
	IBlock1Tex.free();
	IBlock2Tex.free();
}

void Grid::loadMedia()
{
	IBlockTex.loadFromFile("media/IBlockTex.png");
	JBlockTex.loadFromFile("media/JBlockTex.png");
	LBlockTex.loadFromFile("media/LBlockTex.png");
	OBlockTex.loadFromFile("media/OBlockTex.png");
	SBlockTex.loadFromFile("media/SBlockTex.png");
	TBlockTex.loadFromFile("media/TBlockTex.png");
	ZBlockTex.loadFromFile("media/ZBlockTex.png");
	IBlock1Tex.loadFromFile("media/IBlock1Tex.png");
	IBlock2Tex.loadFromFile("media/IBlock2Tex.png");
}

void Grid::setGrid(Vector2<int> pos, int shape)
{	
	GRID[pos.y / GRID_SIZE][(pos.x / GRID_SIZE) - 2] = shape;
}

void Grid::initTempGrid()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			TEMP_GRID[y][x] = GRID[y][x];
		}
	}
}

void Grid::setTempGrid(Vector2<int> pos, int shape)
{
	if (TEMP_GRID[0][0] == -1)
		initTempGrid();
	
	TEMP_GRID[pos.y / GRID_SIZE][(pos.x / GRID_SIZE) - 2] = shape;
}

int Grid::getFitClearTemp()
{	
	checkRows(TEMP_GRID, false);

	int height = 0;
	int holes = 0;
	int bumpiness = 0;
	int tmpHeights[GRID_WIDTH] = { 0 };

	for (int x = 0; x < GRID_WIDTH+1; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			if (TEMP_GRID[y][x] != 0 && x < GRID_WIDTH)
			{
				tmpHeights[x] = GRID_HEIGHT - y;
				height += tmpHeights[x];

				break;
			}
		}

		int diff = abs((x != 0 ? tmpHeights[x - 1] : 0) - (x < GRID_WIDTH ? tmpHeights[x] : 0));
		bumpiness += diff;
	}

	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 1; y < GRID_HEIGHT; y++)
		{
			if (TEMP_GRID[y][x] == 0 && TEMP_GRID[y-1][x] != 0)
			{
				holes++;
			}
		}
	}
	
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			TEMP_GRID[y][x] = -1;
		}
	}

	return int(height+holes+(bumpiness*0.5)-(clearCount*5));
}

bool Grid::checkGrid(Vector2<int> pos)
{
	if (pos.y / GRID_SIZE >= GRID_HEIGHT)
		return true;

	if (pos.x / GRID_SIZE < 2)
		return true;

	if (pos.x / GRID_SIZE >= GRID_WIDTH + 2)
		return true;

	checkRows(GRID);
	return GRID[pos.y / GRID_SIZE][(pos.x / GRID_SIZE) - 2] != 0;
}

void Grid::printGrid()
{	
	/*system("CLS");
	
	for (int y = 0; y < SCREEN_HEIGHT; y += GRID_SIZE)
	{
		for (int x = 64; x < GRID_LENGTH; x += GRID_SIZE)
		{
			std::cout << GRID[y / GRID_SIZE][(x / GRID_SIZE) - 2] << " ";
		}

		std::cout << std::endl;
	}*/
}

bool Grid::checkRows(int grid[][GRID_WIDTH], bool sendMsg)
{
	clearCount = 0;
	
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		bool fullRow = true;
		
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			fullRow = grid[y][x] != 0;
			if (!fullRow) break;
		}

		if (fullRow)
		{
			clearRow(grid, y, sendMsg);
			clearCount++;
		}
	}

	return false;
}

void Grid::clearRow(int grid[][GRID_WIDTH], int clearY, bool sendMsg)
{
	if (sendMsg && !doneBlinking)
	{
		rowBlinking = clearY*GRID_SIZE;
		blinking = true;
		return;
	}
	
	for (int y = clearY; y >= 0; y--)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			if (y > 0)
				grid[y][x] = grid[y-1][x];
			else
				grid[y][x] = 0;
		}
	}

	printGrid();

	if (sendMsg)
	{
		Game::game()->clearRow(clearY);
		blinkCount = 0;
		blinking = true;
	}
}

void Grid::render()
{
	for (int y = 0; y < SCREEN_HEIGHT; y += GRID_SIZE)
	{
		for (int x = 64; x < GRID_LENGTH; x += GRID_SIZE)
		{
			int block = GRID[y / GRID_SIZE][(x / GRID_SIZE) - 2];
			
			if (block != 0 && block < 10)
				textures[block - 1]->render(x, y);

			else if (block >= 10)
			{
				int b = block / 10;
				int r = block - (b * 10);

				textures[b - 1]->render(x + rotOff[r].x, y + rotOff[r].y, 0, ((r - 1) % 4) * 90);
			}
		}
	}

	if (blinking)
	{
		if (blinkCount % blinkRate <= (blinkRate / 2))
		{
			SDL_Rect fillRect = { 64, rowBlinking, GRID_LENGTH - 64, GRID_SIZE };
			SDL_SetRenderDrawColor(gRenderer, 165, 162, 165, 255);
			SDL_RenderFillRect(gRenderer, &fillRect);
		}
		else if (blinkCount >= blinkRate*2)
		{
			SDL_Rect fillRect = { 64, rowBlinking, GRID_LENGTH - 64, GRID_SIZE };
			SDL_SetRenderDrawColor(gRenderer, 255, 251, 255, 255);
			SDL_RenderFillRect(gRenderer, &fillRect);
		}

		blinkCount++;

		if (blinkCount > blinkRate*2 + (blinkRate/2))
		{
			blinking = false;
			doneBlinking = true;
		}
	}
}

void Grid::clearGrid()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			GRID[y][x] = 0;
		}
	}
}