#include "GA.h"

int GA::arrayToNum(unsigned* input, int start, int endd)
{
	std::stringstream ss;

	for (int i = start; i < endd; i++)
		ss << input[i];

	int result;
	ss >> result;
	return result;
}

unsigned GA::binToDec(unsigned num)
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

void GA::randomizeChromo()
{
	for (int i = 0; i < 7; i++)
	{
		chromo[i] = rand() % 2;
	}
}

void GA::epoch()
{
	randomizeChromo();
	int move = arrayToNum(&chromo[0], 0, 4);
	int rot = arrayToNum(&chromo[0], 4, 7);

	move = binToDec(move);
	rot = binToDec(rot);

	pieceManager->moveByChromo(move, rot);
}