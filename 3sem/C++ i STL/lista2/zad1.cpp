#include <iostream>
#include<memory>

using namespace std;
int n = 5;

class Licznik
{
	public:
		uint64_t count;
		Licznik ()
		{
			count = 1;
		}
		virtual ~Licznik()
		{
			cerr<<"usuwanie obietku, count: "<<this->count<<endl;
		}



};

unique_ptr<Licznik[]> inc (int m, unique_ptr<Licznik[]> tab, int i)
{
	if (m == 0 or m > n)
		return tab;
	int r = rand() % n;
	tab[r].count += i;
	return inc(m - 1, move(tab), i + 1);

}

void write (unique_ptr<Licznik[]> tab)
{
	for(int i = 0 ; i < n; i++)
	{
		cout<<"Element "<<i<<": "<<tab[i].count<<endl;
	}
	//cout<<tab[0].count;
}
void c(int d)
{
	d +=1;
}
int main()
{
	//tablica n wskażników na Liczniki
	// można tez : 
	/* unique_ptr< Licznik , void(*)(Licznik*) > tab ( 
		new Licznik[n],
		[](Licznik *ptr) { delete[] ptr; });*/
	unique_ptr< Licznik[] > tab{new Licznik[n]};
	
	tab = inc(5, move(tab), 1);
	write(move(tab));

	return 0;
}