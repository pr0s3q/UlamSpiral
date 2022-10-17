#include "Mathematic.h"

bool Mathematic::IsPrime(unsigned int number)
{
	if (number % 2 == 0 ||
		number % 3 == 0 ||
		number % 5 == 0 ||
		number % 7 == 0)
		return false;

	return true;
}
