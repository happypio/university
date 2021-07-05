#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
bool blad=0;
string maks = "9223372036854775807";
string mini = "9223372036854775808";
long long int pot10(int a){
    long long int wynik=1;
    for(int i=0;i<a;i++)
        wynik*=10;
    return wynik;
}

int64_t strtoint(string liczba)
{
    if(liczba.size()==0)
    {
        blad=1;
        return 0;
    }
    string porownanie="";
    int64_t wynik=0,i;
    int m=1,j=0,minusik=0;
    if(liczba[0]=='-'){
        minusik=1;
        i=1;
        m=2;
    }
    else
        i=0;
    for(i; i < liczba.size(); i++){
            porownanie+=liczba[i];
            j++;
            if(liczba[i]-'0'>9){
                blad=1;
                return 0;
            }
            wynik+=(liczba[i]-'0')*pot10(liczba.size()-m);
            m++;
        }
    //cout<<endl<<porownanie<<endl;
    if(porownanie.size()>mini.size())
    {
        blad=1;
        return 0;
    }
    if(porownanie.size()==mini.size()){
        if((porownanie>maks&&!minusik)||(porownanie>mini))
        {
            blad=1;
            return 0;
        }
    }
    return wynik;
}

bool czy_pierwsza(int64_t x){
    for(int64_t i=2;i*i<x;i++){
        if(x%i==0)
            return false;
        }
    return true;
}

vector<int64_t> rozklad(int64_t x){
    int64_t pierw = sqrt(x),k=2;
    vector <int64_t> wynik;
    while(x > 1 && k < pierw){
        while(x%k==0){
            wynik.push_back(k);
            x/=k;
        }
        k++;
    }
    //cout<<"hej "<<x<<" ";
    if(x>1)
        wynik.push_back(k);
    return wynik;
}

void wypisz(int i){
    cout<<i<<" * ";
}
int main(int argc, char *argv[])
{
    if(argc==1){
        cerr<<"Nalezy podac przynajmniej jedna liczbe do rozkladu"<<endl;
        return 0;
    }
    for(int i=1;i<argc;i++){
        int byzer=0;
        cout<<argv[i]<<" = ";
        if(argv[i][0]=='-'){
            if(argv[i][1]=='0'){
                cout<<"0";
                byzer=1;
            }
            else
                cout<<"(-1) * ";
        }
        else{
        if(argv[i][0]=='0'){
            cout<<"0";
            byzer=1;
            }
        else
            cout<<"1 * ";
        }

        int64_t x = strtoint(argv[i]);
        if(blad)
            throw invalid_argument("Invalid argument");
        //cout<<x<<" adawd ";
        //if(czy_pierwsza(x))
            //cout<<x;
        //else
        if(x==-9223372036854775808){
            for(int i=0;i<62;i++)
                cout<<"2 * ";
            cout<<"2";
        }
        else{
            if(!byzer){
                vector <int64_t> wektor = rozklad(x);
                for_each (wektor.begin(), wektor.end()-1,wypisz);
                cout<<wektor[wektor.size()-1];
            }
            }
        cout<<endl;
    }

    return 0;
}
