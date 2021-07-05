#include<iostream>

using namespace std;
enum class Imiona : uint16_t
{
	Marek,
	Franek,
	Basia,
	Kornelia
};
void funkcja (string komunikat, Imiona imie)
{
	switch(imie)
	{
		case Imiona::Marek:
			cout<<"Cześć Marek, twój komunikat: "<<komunikat<<endl;
			break;
		case Imiona::Basia:
			cout<<"Cześć Basia, twój komunikat: "<<komunikat<<endl;
			break;
		case Imiona::Franek:
			cout<<"Cześć Franek, twój komunikat: "<<komunikat<<endl;
			break;
		case Imiona::Kornelia:
			cout<<"Cześć Kornelia, twój komunikat: "<<komunikat<<endl;
			break;
		default:
			cout<<"Nie ma takiego imienia :("<<endl;
	}
}
int main()
{
	funkcja("siemanderko z komputera", Imiona::Franek);
	return 0;
}