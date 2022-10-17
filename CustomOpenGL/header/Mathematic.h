#pragma once

class Mathematic
{
public:

    //---------------------------------------------------------------

    /// <summary>
    /// Check if given number is prime
    /// </summary>
    /// <param name="number"></param>
    /// <returns></returns>
    static bool IsPrime(unsigned int number);

    //---------------------------------------------------------------

    /// <summary>
    /// Returns how many prome numbers are between 0 and given number
    /// </summary>
    /// <param name="number"></param>
    /// <returns></returns>
    static void PrimeAmount(unsigned int number, unsigned int& amount);

    //---------------------------------------------------------------
};