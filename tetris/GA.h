#pragma once
#include "common.h"
#include "PieceManager.h"

class Chromosome
{
private:
	unsigned chromo[CHROMO_LENGTH] = { 0 };
	int arrayToNum(unsigned* input, int start, int end);

public:
	Chromosome();
	int arrayToNum(int start, int end);
	unsigned binToDec(unsigned num);
	void randomizeChromo();
};

class GA
{
private:
	PieceManager* pieceManager;
	Chromosome population[POP_SIZE];
	int index = 0;

public:
	GA(PieceManager* p);

	void epoch();
};