#include "Grid.h"
#include "Game.h"

Grid::Grid()
{

}

void Grid::setGrid(Vector2<int> pos)
{	
	GRID[pos.y / GRID_SIZE][(pos.x / GRID_SIZE) - 2] = true;
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
	return GRID[pos.y / GRID_SIZE][(pos.x / GRID_SIZE) - 2];
}

bool Grid::checkAgainstRow(int x, int row)
{
	return GRID[row][(x / GRID_SIZE) - 2];
}

void Grid::printGrid()
{	
	system("CLS");
	
	for (int y = 0; y < SCREEN_HEIGHT; y += GRID_SIZE)
	{
		for (int x = 64; x < GRID_LENGTH; x += GRID_SIZE)
		{
			std::cout << GRID[y / GRID_SIZE][(x / GRID_SIZE) - 2] << " ";
		}

		std::cout << std::endl;
	}
}

bool Grid::checkRows()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		bool fullRow = true;
		
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			fullRow = GRID[y][x];
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
				GRID[y][x] = false;
		}
	}

	printGrid();
	Game::game()->clearRow(clearY);
}