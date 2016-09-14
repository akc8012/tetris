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
	int height = 0;
	int holes = 0;

	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			if (TEMP_GRID[y][x] != 0)
			{
				height += GRID_HEIGHT - y;
				break;
			}
		}
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
	
	return height+holes;
}

bool Grid::checkGrid(Vector2<int> pos)
{
	if (pos.y / GRID_SIZE >= GRID_HEIGHT)
		return true;

	if (pos.x / GRID_SIZE < 2)
		return true;

	if (pos.x / GRID_SIZE >= GRID_WIDTH + 2)
		return true;

	checkRows();
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

bool Grid::checkRows()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		bool fullRow = true;
		
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			fullRow = GRID[y][x] != 0;
			if (!fullRow) break;
		}

		if (fullRow)
			clearRow(y);
	}

	return false;
}

void Grid::clearRow(int clearY)
{
	for (int y = clearY; y >= 0; y--)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			if (y > 0)
				GRID[y][x] = GRID[y-1][x];
			else
				GRID[y][x] = 0;
		}
	}

	printGrid();
	Game::game()->clearRow(clearY);
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
				int b = block/10;
				int r = block-(b*10);
				
				textures[b-1]->render(x+rotOff[r].x, y+rotOff[r].y, 0, ((r-1) % 4) * 90);
			}
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