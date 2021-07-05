#include<iostream>
#include <iomanip>
#include<cmath>

using namespace std;
double f1(double x)
{

	double s = x - sin(x);
	double res = s*12120/pow(x,3);
	return res;
}
float f2(float x)
{
	float s = x - sin(x);
	float res = s*12120/pow(x,3);
	return res;
}
int main()
{
	cout.precision(32);
	double doub_prec;
	float single_prec;
	for(int i = 11; i <= 20; i++)
	{
		doub_prec = pow(10,-i);
		single_prec = pow(10,-i);
		cout<<doub_prec<<" "<<single_prec<<"\n";
		cout<<sin(doub_prec)<<" "<<sin(single_prec)<<"\n";
		cout<<doub_prec - sin(doub_prec)<<"\n";
		cout<<"single precision dla i = "<<i<<" to "<<f2(single_prec)<<"\n";
		cout<<"double precision dla i = "<<i<<" to "<<f1(doub_prec)<<"\n";
	}
	return 0;
}