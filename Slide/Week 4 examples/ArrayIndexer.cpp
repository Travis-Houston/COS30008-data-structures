
// COS30008, 2022

#include "ArrayIndexer.h"

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

const int& IntArrayIndexer::operator[]( const std::string& aKey ) const
{
    size_t lIndex = 0;
    
    for ( size_t i = 0; i < aKey.size(); i++ )
    {
        lIndex = lIndex * 10 + (aKey[i] - '0');
    }
    
    return (*this)[lIndex];
}
