#include<iostream>
#include<limits>

using namespace std;

int main()
{
	cout << numeric_limits<long long int>::max()<<endl;
	cout << numeric_limits<long long int>::min()<<endl;
	cout << numeric_limits<long long int>::digits<<endl;
	cout << numeric_limits<long long int>::digits10<<endl;
	return 0;
}