#include "Grid.h"

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

	return GRID[pos.y / GRID_SIZE][(pos.x / GRID_SIZE) - 2];
}

void Grid::printGrid()
{	
	for (int x = 64; x < GRID_LENGTH; x += GRID_SIZE)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y += GRID_SIZE)
		{
			if (GRID[y / GRID_SIZE][(x / GRID_SIZE) - 2])
			{
				std::cout << x << ", " << y << std::endl;
				std::cout << GRID[y / GRID_SIZE][(x / GRID_SIZE) - 2] << std::endl;
			}
		}
	}
}