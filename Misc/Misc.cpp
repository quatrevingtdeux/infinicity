
#include <cassert>
#include <cstdlib>

#include "Misc.h"

int rand_int(int min, int max)
{
	assert(min < max && rand() != rand());
	return min + rand() % (max - min);
}

double rand_double(double min, double max)
{
	assert(min < max && rand() != rand());
	double random = ((double) rand()) / (double) RAND_MAX;
	double range = max - min;
	return min + (random * range);
}
