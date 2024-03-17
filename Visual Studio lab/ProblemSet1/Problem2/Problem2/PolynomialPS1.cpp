#include <iostream>
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial() : fDegree(0)
{
    for (size_t i = 0; i <= MAX_DEGREE; i++) {
        fCoeffs[i] = 0.0;
    }
}

Polynomial Polynomial::operator*(const Polynomial& aRHS) const {
    Polynomial multiplyResult;
    multiplyResult.fDegree = fDegree + aRHS.fDegree;

    // Multiply polynomials using nested loops
    for (size_t i = 0; i <= fDegree; i++) {
        for (size_t j = 0; j <= aRHS.fDegree; j++) {
            multiplyResult.fCoeffs[i + j] += fCoeffs[i] * aRHS.fCoeffs[j];
        }
    }

    return multiplyResult;
}

bool Polynomial::operator==(const Polynomial& aRHS) const
{
    bool Result = fDegree == aRHS.fDegree;

    // Compare coefficients of polynomials
    for (size_t i = 0; i <= fDegree; i++)
    {
        if (fCoeffs[i] != aRHS.fCoeffs[i])
        {
            Result = false;
        }
    }
    return Result;
}

double Polynomial::operator()(double aX) const
{
    double result = 0.0;

    // Evaluate polynomial using Horner's method
    for (int i = fDegree; i >= 0; i--)
    {
        result += fCoeffs[i] * pow(aX, i);
    }

    return result;
}

Polynomial Polynomial::getDerivative() const
{
    Polynomial derivative;
    derivative.fDegree = fDegree - 1;

    // Compute the derivative of the polynomial
    for (int i = fDegree; i >= 1; i--)
    {
        derivative.fCoeffs[i - 1] = fCoeffs[i] * i;
    }

    return derivative;
}

Polynomial Polynomial::getIndefiniteIntegral() const
{
    Polynomial integral;
    integral.fDegree = fDegree + 1;

    // Compute the indefinite integral of the polynomial
    for (int i = fDegree + 1; i >= 1; i--)
    {
        integral.fCoeffs[i] = fCoeffs[i - 1] / i;
    }

    return integral;
}

double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const
{
    Polynomial indefiniteIntegral = getIndefiniteIntegral();
    double integralLow = 0.0;
    double integralHigh = 0.0;

    // Compute the definite integral using the indefinite integral
    for (int i = fDegree + 1; i >= 0; i--)
    {
        integralLow += indefiniteIntegral.fCoeffs[i] * pow(aXLow, i);
        integralHigh += indefiniteIntegral.fCoeffs[i] * pow(aXHigh, i);
    }

    return integralHigh - integralLow;
}

istream& operator>>(istream& aIStream, Polynomial& aObject) {
    aIStream >> aObject.fDegree;

    // Read the polynomial coefficients from input
    for (int i = aObject.fDegree; i >= 0; i--) {
        aIStream >> aObject.fCoeffs[i];
    }

    return aIStream;
}

ostream& operator<<(ostream& aOStream, const Polynomial& aObject) {
    bool lPrint = false;

    // Print the polynomial expression
    for (int i = aObject.fDegree; i >= 0; i--) {
        if (aObject.fCoeffs[i] != 0.0) {
            if (lPrint) {
                aOStream << " + ";
            }
            else {
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