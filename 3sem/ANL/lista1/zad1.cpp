#include<iostream>
#include<cmath>
using namespace std;

double f(double x)
{
	double s = sqrt(pow(x,11) + 1.0);
	double res = (s - 1.0)*4040/pow(x,11);
	return res;
}

int main()
{
	double x = 0.001;
	cout.precision(17);
	cout<<f(x)<<"\n";
	return 0;
}