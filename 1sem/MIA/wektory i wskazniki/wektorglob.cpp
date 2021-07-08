#include<iostream>
#include<vector>
using namespace std;
vector<int> k;
void wektor ()
{
    k.push_back(3);
}
void wektor2(vector<int> &z)
{
    z.push_back(8);
}
int main()
{
    k.push_back(2);
    k.push_back(4);
    vector<int>::iterator i=k.begin()+1;
    wektor();
    cout<<k.size()<<" "<<*i<<endl;
    wektor2(k);
    cout<<k.size()<<" "<<*i+20<<endl;//dodaje wartosc do zmiennej w wektorze
    i=k.begin()+2;
    cout<<k.size()<<" "<<*i<<" "<<k[3];
    return 0;
}
