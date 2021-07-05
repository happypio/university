#include<iostream>
#include<memory>

using namespace std;

int main()
{
	shared_ptr< int > s(new int(1));
	weak_ptr< int > w1 = s;
	if (auto tmp{w1.lock()}; tmp)
		cout<<"W1 wskazuje na s = "<<*tmp<<endl;
	else
		cout<<"W1 jest wiszacy!"<<endl;

	s.reset(new int(2));
	weak_ptr<int > w2 = s;

	cout<<"--------zmieniamy wskaznik poczatkowy s----------"<<endl;
	if (auto tmp{w1.lock()}; tmp)
		cout<<"W1 wskazuje na s = "<<*tmp<<endl;
	else
		cout<<"W1 jest wiszacy!"<<endl;

	if (auto tmp{w2.lock()}; tmp)
		cout<<"W2 wskazuje na s = "<<*tmp<<endl;
	else
		cout<<"W2 jest wiszacy!"<<endl;




	return 0;
}