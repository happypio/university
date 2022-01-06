#include<iostream>
#include<vector>
using namespace std;
int goal[100003], value[100003], licznik=0;
vector<int>wynik;


void dfs(bool dojscie[],vector<int>drzewo[],int x,bool czy_zmiana,bool czy_zmiana2)
{
    dojscie[x]=1;
    if(czy_zmiana)
    {
        if(goal[x]==1)
            goal[x]=0;
        else
            goal[x]=1;
    }
    if(goal[x]!=value[x])
    {
        goal[x]=value[x];
        czy_zmiana=!czy_zmiana;
        licznik++;
        wynik.push_back(x);
    }

    for(int unsigned i=0;i<drzewo[x].size();i++)
        if(dojscie[drzewo[x][i]]!=1)
            dfs(dojscie,drzewo,drzewo[x][i],czy_zmiana2,czy_zmiana);

}

int main()
{
    ios_base::sync_with_stdio(false);
    int n,a,b;
    cin>>n;
    bool dojscie[n+1]={0};
    vector<int> drzewo[n+1];
    for(int i=1;i<n;i++)
    {
        cin>>a>>b;
        drzewo[a].push_back(b);
        drzewo[b].push_back(a);
    }

    for(int i=1;i<=n;i++)
    {
        cin>>value[i];
    }

    for(int i=1;i<=n;i++)
    {
        cin>>goal[i];
    }

    dfs(dojscie,drzewo,1,0,0);
    cout<<licznik<<endl;
    for(int unsigned i=0;i<wynik.size();i++)
        cout<<wynik[i]<<endl;
    return 0;
}
