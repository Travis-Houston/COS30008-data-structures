#include <iostream>
#include "BernsteinBasisPolynomial.h"

using namespace std;

int main()
{
	BernsteinBasisPolynomial bba(0, 4);
	BernsteinBasisPolynomial bbb(1, 4);
	BernsteinBasisPolynomial bbc(2, 4);
	BernsteinBasisPolynomial bbd(3, 4);
	BernsteinBasisPolynomial bbe(4, 4);
	for (double i = 0.0; i < 1.1; i += 0.2)
	{
		cout << "4th degree Bernstein basis polynomial at "
			<< i << " = "
			<< bba(i) + bbb(i) + bbc(i) + bbd(i) + bbe(i)
			<< endl;
	}
}