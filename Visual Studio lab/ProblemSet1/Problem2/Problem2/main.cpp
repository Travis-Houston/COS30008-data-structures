#include <iostream>
#include "Polynomial.h" // Include the header file for the Polynomial class
using namespace std;

int main()
{
	Polynomial A; // Declare an instance of the Polynomial class called A

	cout << "Specify polynomial:" << endl;
	cin >> A; // Input the polynomial coefficients for A

	cout << "A = " << A << endl; // Print the polynomial A

	double x;
	cout << "Specify value of x:" << endl;
	cin >> x; // Input the value of x

	cout << "A(x) = " << A(x) << endl; // Evaluate A at x and print the result

	Polynomial B; // Declare another instance of the Polynomial class called B

	if (B == B.getDerivative()) // Check if B is equal to its derivative
	{
		cout << "Derivative programmatically sound." << endl;
	}
	else
	{
		cout << "Derivative is broken." << endl;
	}

	if (A == A.getIndefiniteIntegral().getDerivative()) // Check if A is equal to the derivative of its indefinite integral
	{
		cout << "Polynomial operations are sound." << endl;
	}
	else
	{
		cout << "Polynomial operations are broken." << endl;
	}

	cout << "Indefinite integral of A = " << A.getIndefiniteIntegral() << endl; // Compute and print the indefinite integral of A

	cout << "Derivative of A = " << A.getDerivative() << endl; // Compute and print the derivative of A

	cout << "Derivative of indefinite integral of A = " << A.getIndefiniteIntegral().getDerivative() << endl; // Compute and print the derivative of the indefinite integral of A

	cout << "Definite integral of A(xlow=0, xhigh=12.0) = " << A.getDefiniteIntegral(0, 12.0) << endl; // Compute and print the definite integral of A from 0 to 12.0
}