#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial() : fDegree(0) 
{
    for (size_t i = 0; i <= MAX_DEGREE ; i++) {
        fCoeffs[i] = 0.0; 
    }
}

bool Polynomial::operator==( const Polynomial& aRHS ) const 
{
    bool Result = fDegree == aRHS.fDegree;

    for(size_t i = 0; i <= fDegree ; i++) 
    {
        if(fCoeffs[i] != aRHS.fCoeffs[i]) 
        {
            Result = false;
        }
    }
    return Result;
}

Polynomial Polynomial::operator*(const Polynomial& aRHS) const {
    Polynomial multiplyResult;
    multiplyResult.fDegree = fDegree + aRHS.fDegree;

    for (size_t i = 0; i <= fDegree; i++) {
        for (size_t j = 0; j <= aRHS.fDegree; j++) {
            multiplyResult.fCoeffs[i + j] += fCoeffs[i] * aRHS.fCoeffs[j];
        }
    }

    return multiplyResult;
}

istream& operator>>(istream& aIStream, Polynomial& aObject) {
    aIStream >> aObject.fDegree;

    for (int i = aObject.fDegree; i >= 0; i--) {
        aIStream >> aObject.fCoeffs[i];
    }

    return aIStream;
}

ostream& operator<<(ostream& aOStream, const Polynomial& aObject) {
    bool lPrint = false;

    for (int i = aObject.fDegree; i >= 0; i--) {
        if (aObject.fCoeffs[i] != 0.0) {
            if (lPrint) {
                aOStream << " + ";
            } else {
                lPrint = true;
            }

            double coeff = abs(aObject.fCoeffs[i]);
            if (coeff != 1.0 || i == 0)
                aOStream << aObject.fCoeffs[i];

            if (i > 0)
                aOStream << "x";

            if (i > 1)
                aOStream << "^" << i;
        }
    }

    return aOStream;
}