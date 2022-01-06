#include<iostream>
#include<vector>


using namespace std;
vector<int>droga;

void dfs(bool dojscie[],vector<int>tab[],int x)
{
    dojscie[x]=1;
    for(int unsigned i=0;i<tab[x].size();i++)
    {
        if(!dojscie[tab[x][i]])
        {
            dfs(dojscie,tab,tab[x][i]);

        }
    }
    droga.push_back(x);
}

int main()
{
    ios_base::sync_with_stdio(false);
    string wyraz;
    int n;
    cin>>n;
    vector<int> tab[n];
    for(int i=0;i<n;i++)
    {
        cin>>wyraz;
        for(int j=0;j<n;j++)
            if(j!=i)
            {
                if(wyraz[j]=='1')
                    tab[i].push_back(j);
            }
    }

    if(n==1)
    {
        cout<<0;
        return 0;
    }

    if(tab[0].size()==0)
    {
        cout<<"impossible";
        return 0;
    }
    else
    {
        bool dojscie[n]={0};
        dfs(dojscie,tab,0);
        for(int i=0;i<n;i++)
        {
          if(dojscie[i]==0)
            {
            cout<<"impossible";
            return 0;
            }
        }
    }

    for(vector<int>::iterator i=droga.begin();i!=droga.end();i++)
        cout<<*i<<" ";
    return 0;
}
