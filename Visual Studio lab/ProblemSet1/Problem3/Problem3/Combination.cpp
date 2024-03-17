#include "Combination.h"

Combination::Combination(size_t aN, size_t aK)
    : fN(aN), fK(aK)
{
}

size_t Combination::getN() const
{
    return fN;
}

size_t Combination::getK() const
{
    return fK;
}

unsigned long long Combination::operator()() const
{
    unsigned long long result = 1;

    // Calculate the combination using the formula
    // (n choose k) = n! / (k! * (n - k)!)
    for (size_t i = 1; i <= fK; ++i)
    {
        // Multiply the result by (fN - i + 1)
        // to compute the numerator of the combination formula
        result *= fN - i + 1;

        // Divide the result by i
        // to compute the denominator of the combination formula
        result /= i;
    }

    return result;
}