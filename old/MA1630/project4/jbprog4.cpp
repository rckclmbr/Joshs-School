// Joshua Braegger
// 11/1/2005
// Program jbprog4.cpp
// Function: Counting and probability.

#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

double Permutation(long, long);
double Combination(long, long);
double HyperGeometric(long, long, long, long);
double Binomial(double, long, long);
double NegativeBinomial(double, long, long);
double Poisson(double, long);
double factorial(double);

int main()
{
	cout << "Problem 1:" << endl;
	cout << "a: " << (long)Permutation(23,5) << endl;
	cout << "b: " << Combination(23,5);
	cout << endl << endl;

	cout << "Problem 2:" << endl;
	cout << HyperGeometric(62,5,9,2);
	cout << endl << endl;

	cout << "Problem 3:" << endl;
	cout << Binomial(.074,28,3);
	cout << endl << endl;

	cout << "Problem 4:" << endl;
	cout << NegativeBinomial(.074,25,2);
	cout << endl << endl;

	cout << "Problem 5:" << endl;
	cout << "a: " << Binomial(.023,115,4) << endl;
	cout << "b: " << Poisson((115 * .023),4) << endl;
	cout << "c: " << "very good";
	cout << endl << endl;


	return 0;
}

double Permutation(long N, long X)
{
	double tmpN = (double)N;

	for(int count = 1; count < X; count++)
	{
		tmpN = tmpN * (N - count);	
	}

	return tmpN;
}

double Combination(long N, long X)
{
	double tmp = 1;
	double tmpN = 1;
	int y = 1;

	// C(N,0) is 1
	if(X == 0)
		return 1;

	// If N-X is smaller, we have to loop all the way
	if( X < (N-X) )
	{
		int stop = (N-(X-1));
		
		for(int count=N; count >= stop; count--)
		{
			tmp = (double)count / y;
			tmpN = tmpN * tmp;
			y++;
		}
	}
	// If N-X is larger, then we loop less
	else
	{
		int stop = X;
		for(int count=N; count > stop; count--)
		{
			tmp = (double)count / y;
			tmpN = tmpN * tmp;
			y++;
		}
	}

	return tmpN;
}

double HyperGeometric(long Np, long Kp, long N, long X)
{
	double tmp;

	tmp = ( Combination(Kp,X) * Combination(Np-Kp,N-X) );
	tmp = tmp / Combination(Np,N);

	return tmp;
}

double Binomial(double P, long N, long X)
{
	double tmp;

	tmp = Combination(N,X) * pow(P,(double)X) * pow( (1-P),(double)(N-X) );

	return tmp;
}

double NegativeBinomial(double P, long N, long X)
{
	double tmp;

	tmp = (Binomial(P,(N-1),(X-1)) * P);

	return tmp;
}

double Poisson(double Xmean, long X)
{
	const double e = 2.71828183;
	double tmp;

	tmp = pow(e,(double)(-1 * Xmean)) * (pow(Xmean,(double)X) / (factorial(X) ));
	return tmp;
}

double factorial(double x)
{
	if(x == 1)
		return 1;
	return factorial(x-1) * x;
}
