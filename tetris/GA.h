#pragma once
#include "common.h"
#include "PieceManager.h"

class Chromosome
{
private:
	int chromo[CHROMO_LENGTH] = { -1, -1, -1, -1, -1, -1, -1 };
	int fitness;
	int arrayToNum(int* input, int start, int end);

public:
	Chromosome();
	int arrayToNum(int start, int end);
	int binToDec(int num);
	void randomizeChromo();

	int getFitness() { return fitness; }
	void setFitness(int _fitness) { fitness = _fitness; }
	void setChromo(int ndx, int val) { chromo[ndx] = val; }
	int getChromo(int ndx) const { return chromo[ndx]; }
	void reset();
};

class GA
{
private:
	PieceManager* pieceManager;

	Chromosome populationA[POP_SIZE];
	Chromosome populationB[POP_SIZE];
	Chromosome* pop = populationA;
	Chromosome* buffer = populationB;

	void calcFitnessValues();
	void sortByFitness();
	int calcTotalFitness();
	Chromosome* rouletteWheel();
	void mate(const Chromosome* mom, const Chromosome* dad, int ndx);

public:
	GA::GA(PieceManager* p) : pieceManager(p) {}
	~GA() {}

	void epoch();
};