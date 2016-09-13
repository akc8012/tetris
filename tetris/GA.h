#pragma once
#include "common.h"
#include "PieceManager.h"
#include <sstream>

class GA
{
private:
	unsigned chromo[CHROMO_LENGTH] = {0};
	PieceManager* pieceManager;

	int arrayToNum(unsigned* input, int start, int endd);
	unsigned binToDec(unsigned num);

public:
	GA(PieceManager* p) : pieceManager(p) {}

	void randomizeChromo();
	void epoch();
};