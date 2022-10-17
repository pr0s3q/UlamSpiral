#include "Mathematic.h"

//---------------------------------------------------------------

bool Mathematic::IsPrime(unsigned int number)
{
    if (number == 2 || number == 3)
        return true;

    if (number <= 1 || number % 2 == 0 || number % 3 == 0)
        return false;

    for (int i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    }

    return true;
}

//---------------------------------------------------------------

void Mathematic::PrimeAmount(unsigned int number, unsigned int& amount)
{
    for (int i = 1; i <= number; i++)
    {
        if (IsPrime(i))
            amount++;
    }
}

//---------------------------------------------------------------
