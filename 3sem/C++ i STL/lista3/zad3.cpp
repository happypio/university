#include<iostream>
#include<ratio>

using namespace std;

template < int N >
class harmonic : public ratio_add< ratio < 1 , N > , harmonic < N - 1 > > {};

template < >
class harmonic < 1 > : public ratio< 1 , 1 > {};


int main()
{
	// testing 
	typedef harmonic < 44 > n1;
	typedef harmonic < 45 > n2;
	typedef harmonic < 46 > n3;

	//so the biggest harmonic sum consists of 46 numbers

	// typedef harmonic < 47 > n4; // error: static assertion failed: overflow in addition
	// typedef harmonic < 48 > n5; // error: static assertion failed: overflow in addition
	cout << "Sum of 46 harmonic numbers is: " 
		<< n3::num << " / " << n3::den << endl;
	return 0;
}