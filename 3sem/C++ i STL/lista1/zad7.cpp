#include<iostream>
#include<string>
using namespace std;
void konwertuj(string data)
{
	string miesiac;
	switch( auto mies { stoi( data.substr(3,2) ) } )
	{
		case 1:
			miesiac = "stycznia";
			break;
		case 2:
			miesiac = "lutego";
			break;
		case 3:
			miesiac = "marca";
			break;
		case 4:
			miesiac = "kwietnia";
			break;
		case 5:
			miesiac = "maja";
			break;
		case 6:
			miesiac = "czerwca";
			break;
		case 7:
			miesiac = "lipca";
			break;
		case 8:
			miesiac = "sierpnia";
			break;
		case 9:
			miesiac = "wrzesnia";
			break;
		case 10:
			miesiac = "pazdziernika";
			break;
		case 11:
			miesiac = "listopada";
			break;
		case 12:
			miesiac = "grudnia";
			break;

		default:
			cout<<"Bledna data"<<endl;
			return;
	}
	cout<<stoi(data)<<" "<<miesiac<<" "<<stoi(data.substr(6,4))<<endl;;

}
int main()
{
	cout<<"wpisz date w formacie DD-MM-RRRR"<<endl;
	string data;
	cin>>data;
	konwertuj(data);
	return 0;
}