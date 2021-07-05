#include<iostream>
#include<limits>

using namespace std;

int main()
{
	cout << "wartosci max i min dla float:" << endl;
	cout << numeric_limits<float>::max() << endl;
	cout << numeric_limits<float>::lowest() << endl;
	cout << "wartosc najblizej zera i roznica miedzy 1 a 1 + epsilon dla float:" << endl;
	cout << numeric_limits<float>::min() << endl;
	cout << numeric_limits<float>::epsilon() << endl;
	cout << "wartosci max i min dla float:" << endl;
	cout << numeric_limits<double>::max() << endl;
	cout << numeric_limits<double>::lowest() << endl;
	cout << "wartosc najblizej zera i roznica miedzy 1 a 1 + epsilon dla double:" << endl;
	cout << numeric_limits<double>::min() << endl;
	cout << numeric_limits<double>::epsilon() << endl;
	return 0;
}