#include<iostream>
#include<vector>
using namespace std;

vector<int> wektor;

void pusz_bak()
{
    wektor.push_back(20);
}
int main()
{
    wektor.push_back(10);
    pusz_bak();
    vector<int>::iterator k=wektor.begin();
    pusz_bak();
    cout<<*(k+2);//musimy wywolac pusz bak przed przypisanie wartosci k=wektor.begin()
    return 0;
}
