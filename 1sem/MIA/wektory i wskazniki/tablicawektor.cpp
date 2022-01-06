#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int> tab[10];
    //tab[1][2]=3;
    tab[1].push_back(2);
    cout<<tab[1].size()<<" "<<tab[1][0]<<" "<<tab[0].size()<<endl;
    vector<int> tab_wektorow[10];
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<i;j++)
            tab_wektorow[i].push_back(j);
    }

    for(int i=0;i<10;i++)
    {
        cout<<"wektor "<<i<<" a jego rozmiar to "<<tab_wektorow[i].size()<<endl;
        for(int unsigned j=0;j<tab_wektorow[i].size();j++)
        {
            cout<<tab_wektorow[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
