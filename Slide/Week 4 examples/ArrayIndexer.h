
// COS30008, 2022

#pragma once

#include <string>

class IntArrayIndexer
{
private:
    
    const int* fArray;
    size_t fSize;
    
public:
    
    IntArrayIndexer( const int aArray[], size_t aSize );
    
    const size_t size() const;
    const int& operator[]( const size_t aIndex ) const;
    const int& operator[]( const std::string& aKey ) const;
};
