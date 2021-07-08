#include<iostream>
#include<vector>
using namespace std;

void dfs_mod(bool dojscie[], vector<long long> drzewo[], long long x, long long m, long long napotkane_koty, bool koty[])
{
    long long napotkane=napotkane_koty;
    if(koty[x]==1)
        napotkane++;
    if(koty[x]==0)
        napotkane=0;
    //cout<<napotkane<<" "<<x<<endl;
    if(napotkane<=m)
    {
    dojscie[x]=1;
    for(long long i=0;i<drzewo[x].size();i++)
        if(dojscie[drzewo[x][i]]==0)
            dfs_mod(dojscie,drzewo,drzewo[x][i],m,napotkane,koty);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    long long n,m,a,b,napotkane_koty=0;
    cin>>n>>m;
    bool koty[n+1]={0},dojscie[n+1]={0};
    for(long long i=1;i<=n;i++)
        cin>>koty[i];
    vector<long long> drzewo[n+1];
    for(long long i=1;i<n;i++)
    {
        cin>>a>>b;
        drzewo[a].push_back(b);
        drzewo[b].push_back(a);
    }
    //if(koty[1]==1)
        //napotkane_koty=1;

    dfs_mod(dojscie,drzewo,1,m,napotkane_koty,koty);
    long long suma=0;
    for(long long i=2;i<=n;i++)
    {
        //cout<<endl<<dojscie[i]<<" ";
        if(dojscie[i]==1 and drzewo[i].size()==1)

            suma++;
    }
    cout<<suma;



    return 0;


}
