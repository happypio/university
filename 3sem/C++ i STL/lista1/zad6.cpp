#include<iostream>
#include<cmath>

using namespace std;
int main()
{
	double a,b,c;
	cin>>a>>b>>c;
	if(auto delta {b * b - 4 * (a * c)}; delta == 0)
		cout<<"x "<< -b / (2 * a)<<endl;
	else if (delta > 0)
	{
		cout<<"x1 "<<(-b - sqrt(delta))/(2 * a)<<endl;
		cout<<"x2 "<<(-b + sqrt(delta))/(2 * a)<<endl;
	}
	else
		cout<<"Brak miejsc zerowych"<<endl;
	return 0;
}