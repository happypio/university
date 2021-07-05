#include<iostream>

using namespace std;

auto Lucas(uint32_t n)
{
	if(n == 0)
		return 2;
	if(n == 1)
		return 1;
	return Lucas(n - 1) + Lucas(n - 2);
}

int main()
{
	cout<<Lucas(10);
	return 0;
}