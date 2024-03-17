
// COS30008, 2022

#include "ArrayIndexerWithLambda.h"

#include <stdexcept>

using namespace std;

IntArrayIndexer::IntArrayIndexer( const int aArray[], size_t aSize ) :
    fArray(aArray),
    fSize(aSize)
{}

const size_t IntArrayIndexer::size() const
{
    return fSize;
}

const int& IntArrayIndexer::operator[]( const size_t aIndex ) const
{
    if ( aIndex < fSize )
    {
        return fArray[aIndex];
    }
    else
    {
        throw out_of_range( "Illegal array index." );
    }
}
const int& IntArrayIndexer::get( const std::string& aKey, StringMap aFunc ) const
{
    return (*this)[aFunc(aKey)];
}
