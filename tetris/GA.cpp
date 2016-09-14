#include "GA.h"

Chromosome::Chromosome()
{
	randomizeChromo();
}

int Chromosome::arrayToNum(int* input, int start, int end)
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

int Chromosome::binToDec(int num)
{
	unsigned res = 0;

	for (int i = 0; num > 0; ++i)
	{
		if ((num % 10) == 1)
			res += (1 << i);

		num /= 10;
	}

	return (int)res;
}

void Chromosome::randomizeChromo()
{	
	for (int i = 0; i < 7; i++)
	{
		chromo[i] = rand() % 2;
	}
}

void GA::epoch()
{	
	population[0].randomizeChromo();

	int move = population[0].arrayToNum(0, 4);
	int rot = population[0].arrayToNum(4, 7);

	move = population[0].binToDec(move);
	rot = population[0].binToDec(rot);

	int fitness = pieceManager->moveByChromo(move, rot);
}