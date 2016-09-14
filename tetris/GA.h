#pragma once
#include "common.h"
#include "PieceManager.h"

class Chromosome
{
private:
	int chromo[CHROMO_LENGTH] = { 0 };
	int fitness;
	int arrayToNum(int* input, int start, int end);

public:
	Chromosome();
	int arrayToNum(int start, int end);
	int binToDec(int num);
	void randomizeChromo();

	int getFitness() { return fitness; }
	void setFitness(int _fitness) { fitness = _fitness; }
};

class GA
{
private:
	PieceManager* pieceManager;
	Chromosome population[POP_SIZE];

public:
	GA::GA(PieceManager* p) : pieceManager(p) {}
	~GA() {}

	void epoch();
};