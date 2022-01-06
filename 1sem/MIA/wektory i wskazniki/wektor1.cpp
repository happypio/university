#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int>::iterator x;
    vector <int> k;
    cout<<k.size()<<endl<<endl;
    for(int i=0;i<10;i++)
        k.push_back(i+1);
    cout<<k.size()<<endl<<endl;
    x=k.begin();
    cout<<*x<<endl<<endl;
    for(vector<int>::iterator y=x;y!=k.end();y++)
        cout<<*y<<" ";
    cout<<endl<<endl;
    int tab[5]={11,12,13,14,15};
    vector<int> drugi(tab,tab+5);
    k.insert(k.begin()+1,100);
    cout<<k.size()<<endl<<endl;
    k.insert(k.begin()+1,drugi.begin(),drugi.end()-1);
    for(vector<int>::iterator y=x;y!=k.end();y++)
        cout<<*y<<" ";
    k.erase(k.begin(),k.begin()+10);
    cout<<endl<<endl<<k.size();
    k.pop_back();
    cout<<endl<<endl<<k.size()<<endl<<endl;
    for(vector<int>::iterator y=x;y!=k.end();y++)
        cout<<*y<<" ";
    k.push_back(8);
    cout<<endl<<endl;
    for(vector<int>::iterator y=x;y!=k.end();y++)
        cout<<*y<<" ";
    vector<int>::iterator y=k.begin();
    cout<<endl<<*(y+1);
    int i;
    return 0;
}
