
// COS30008, 2022

#include "ArrayIndexerWithLambda.h"

#include <iostream>

using namespace std;

int unused_main()
{
    int lArray[] = { 1, 2, 3, 4, 5 };
    IntArrayIndexer lIndexer( lArray, sizeof( lArray ) / sizeof( int ) );
    
    string lBinaryKeys[] = { "000", "001", "010", "011", "100" };
    int lSum = 0;
    
    auto lMapBinary = [] ( const std::string& aNumber )
    {
        size_t lIndex = 0;
         
        for ( size_t i = 0; i < aNumber.size(); i++ )
        {
            lIndex = (lIndex << 1) + (aNumber[i] - '0');
        }
        
        return lIndex;
    };
    
    for ( size_t i = 0; i < lIndexer.size(); i++ )
    {
        lSum += lIndexer.get( lBinaryKeys[i], lMapBinary );
    }
    
    cout << "Indexed sum of [1,2,3,4,5] is " << lSum << endl;
    
    return 0;
}
