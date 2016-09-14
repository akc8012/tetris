#include "GA.h"

Chromosome::Chromosome()
{
	randomizeChromo();
}

int Chromosome::arrayToNum(unsigned* input, int start, int end)
{
	std::stringstream ss;

	for (int i = start; i < end; i++)
		ss << input[i];

	int result;
	ss >> result;
	return result;
}

int Chromosome::arrayToNum(int start, int end)
{
	return arrayToNum(&chromo[0], start, end);
}

unsigned Chromosome::binToDec(unsigned num)
{
	unsigned res = 0;

	for (int i = 0; num > 0; ++i)
	{
		if ((num % 10) == 1)
			res += (1 << i);

		num /= 10;
	}

	return res;
}

void Chromosome::randomizeChromo()
{	
	for (int i = 0; i < 7; i++)
	{
		chromo[i] = rand() % 2;
	}
}

GA::GA(PieceManager* p) : pieceManager(p)
{
	
}

void GA::epoch()
{	
	int move = population[index].arrayToNum(0, 4);
	int rot = population[index].arrayToNum(4, 7);

	move = population[index].binToDec(move);
	rot = population[index].binToDec(rot);

	int fitness = pieceManager->moveByChromo(move, rot);
	index++;
}