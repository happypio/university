#include<iostream>
#include<set>
using namespace std;

int main()
{
	using set_alias = set < string > ;
	set_alias zbior = {"hej" , "to" , "ja" , "raz" , "i" , "/.,;']"};
	for (auto s : zbior)
		cout<<s<<"\n";
	return 0;
}