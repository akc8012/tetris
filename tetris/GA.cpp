#include "GA.h"

Chromosome::Chromosome() : fitness(-1)
{
	
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

void Chromosome::reset(bool onlyFitness)
{
	fitness = -1;

	if (onlyFitness) return;
	
	for (int i = 0; i < CHROMO_LENGTH; i++)
	{
		chromo[i] = -1;
	}
}

void Chromosome::randomizeChromo()
{
	for (int i = 0; i < CHROMO_LENGTH; i++)
	{
		chromo[i] = rand() % 2;
	}
}

void GA::start()
{
	pop = populationA;
	buffer = populationB;
	
	for (int i = 0; i < POP_SIZE; i++)
	{
		pop[i].randomizeChromo();
		buffer[i].reset();
	}
}

void GA::epoch()
{	
	calcFitnessValues();
	sortByFitness();

	for (int i = 0; i < POP_SIZE - 1; i += 2)
	{
		Chromosome* mom = rouletteWheel();
		Chromosome* dad = rouletteWheel();
		mate(mom, dad, i);
	}

	int move = pop[0].arrayToNum(0, 4);
	int rot = pop[0].arrayToNum(4, 7);

	move = pop[0].binToDec(move);
	rot = pop[0].binToDec(rot);

	pieceManager->moveByChromo(move, rot, false);

	Chromosome* temp = pop;
	pop = buffer;
	buffer = temp;
}

void GA::finish()
{
	int move = buffer[0].arrayToNum(0, 4);
	int rot = buffer[0].arrayToNum(4, 7);

	move = buffer[0].binToDec(move);
	rot = buffer[0].binToDec(rot);

	pieceManager->moveByChromo(move, rot, true);

	start();
}

void GA::calcFitnessValues()
{
	for (int i = 0; i < POP_SIZE; i++)
	{
		mutate(i);
		
		int move = pop[i].arrayToNum(0, 4);
		int rot = pop[i].arrayToNum(4, 7);

		move = pop[i].binToDec(move);
		rot = pop[i].binToDec(rot);

		int fitness = pieceManager->moveByChromo(move, rot, false);
		pop[i].setFitness(fitness);
	}
}

void GA::sortByFitness()
{
	for (int pass = 1; pass < POP_SIZE; pass++)
	{
		for (int compares = 0; compares < POP_SIZE - pass; compares++)
		{
			if (pop[compares].getFitness() > pop[compares + 1].getFitness())
			{
				Chromosome temp = pop[compares];
				pop[compares] = pop[compares + 1];
				pop[compares + 1] = temp;
			}
		}
	}
}

int GA::calcTotalFitness()
{
	int total = 0;
	for (int i = 0; i < POP_SIZE; i++)
	{
		total += pop[i].getFitness();
	}

	return total;
}

Chromosome* GA::rouletteWheel()
{
	int ndx = 0;
	int spinAmount = rand() % POP_SIZE;
	for (int i = 0; i < spinAmount; i++)
	{
		if (rand() % 8 == 0)
			return &pop[ndx];

		ndx++;
	}

	return &pop[ndx];
}

void GA::mate(const Chromosome* mom, const Chromosome* dad, int ndx)
{
	buffer[ndx].reset();
	buffer[ndx+1].reset();

	double r = rand() % 10;
	r *= 0.1;
	
	if (r >= CROSSOVER_RATE)
	{
		buffer[ndx] = *mom;
		buffer[ndx].reset(true);
		buffer[ndx+1] = *dad;
		buffer[ndx+1].reset(true);
		return;
	}

	int point = rand() % CHROMO_LENGTH;

	for (int i = 0; i < point; i++)
	{
		buffer[ndx].setChromo(i, mom->getChromo(i));
		buffer[ndx+1].setChromo(i, dad->getChromo(i));
	}

	for (int i = point; i < CHROMO_LENGTH; i++)
	{
		buffer[ndx].setChromo(i, dad->getChromo(i));
		buffer[ndx+1].setChromo(i, mom->getChromo(i));
	}
}

void GA::mutate(int ndx)
{
	double r = rand() % 1000;
	r *= 0.001;

	if (r >= MUTATION_RATE)
		return;

	int point = rand() % CHROMO_LENGTH;
	pop[ndx].setChromo(point, !pop[ndx].getChromo(point));
}