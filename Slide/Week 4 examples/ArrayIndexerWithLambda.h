
// COS30008, 2022

#pragma once

#include <string>

#include <functional>

using StringMap = std::function<size_t(const std::string&)>;

class IntArrayIndexer
{
private:
    
    const int* fArray;
    size_t fSize;
    
public:
    
    IntArrayIndexer( const int aArray[], size_t aSize );
    
    const size_t size() const;
    const int& operator[]( const size_t aIndex ) const;

    const int& get( const std::string& aKey,
                    StringMap aFunc = []( const std::string& aNumber )
                        {
                            size_t lIndex = 0;
                    
                            for ( size_t i = 0; i < aNumber.size(); i++ )
                            {
                                lIndex = lIndex * 10 + (aNumber[i] - '0');
                            }
                   
                            return lIndex;
                        }) const;
};
