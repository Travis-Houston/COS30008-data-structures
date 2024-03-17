#include "FibonacciSequence.h"
#include <iostream>
#include <cstdint>
#include <stdexcept>

using namespace std;

FibonacciSequence::FibonacciSequence(uint64_t aLimit)
{
    fPrevious = 0;    // previous Fibonacci number (initially 0)
    fCurrent = 1;     // current Fibonacci number (initially 1)
    fPosition = 1;    // position in the sequence (starts with 1)
    fLimit = aLimit;       // set limit for sequence (0 for no limit)
}

// get current Fibonacci number
const uint64_t& FibonacciSequence::current() const
{
    return fCurrent;
}

void FibonacciSequence::advance() 
{
    if (fPosition > fLimit) {
        throw out_of_range("kjeHÀKJAS");
    }
    uint64_t temp = fCurrent;
    fPosition++;
    fCurrent += fPrevious;
    fPrevious = temp;
    
}

const uint64_t& FibonacciSequence::getLimit() const
{
    return fLimit;
}

void FibonacciSequence::reset() 
{
    fPrevious = 0;    // previous Fibonacci number (initially 0)
    fCurrent = 1;     // current Fibonacci number (initially 1)
    fPosition = 1;    // position in the sequence (starts with 1)
}