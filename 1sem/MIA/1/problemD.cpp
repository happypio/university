#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
vector< pair<int,int> > drzewo[1005];
priority_queue<long long,vector<long long>,greater<long long> > kolejka[1005];
long long d[1005],koszty[1005],koszt=0;
int unsigned k;
void dfs(bool dojscie[],int x,int p,int konst,long long d2[]){
    dojscie[x]=1;
    int j=0;
    for(int unsigned i=0;i<drzewo[x].size();i++){
        if(drzewo[x][i].first==p)
            j=i;
        if(!dojscie[drzewo[x][i].first]){
            dfs(dojscie,drzewo[x][i].first,x,konst,d2);
        }
    }
    d2[x]+=d[x];
    d2[p]+=d2[x];
    if(drzewo[x].size()>0){
        koszt=d2[x]*drzewo[x][j].second;
    if(x!=konst){
    koszty[konst]+=koszt;
    if(kolejka[konst].size()>=k&&k!=0){
        if(koszt>kolejka[konst].top()){
            koszty[konst]=koszty[konst]+kolejka[konst].top()-koszt;
            kolejka[konst].pop();
            kolejka[konst].push(koszt);
        }
    }
    else{
        if(k!=0){
        kolejka[konst].push(koszt);
        koszty[konst]-=koszt;}
    }}}
    //cout<<koszt<<" aktualny wierzch "<<x<<" poprzedni "<<p<<" waga "<<drzewo[x][j].second<<" kosztykonst "<<koszty[konst]<<" kolejkatop "<<kolejka[konst].top()<<endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    int n,u,v,w;
    long long mini=9223372036854775806;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>d[i];
    }
    //if(n==1){
        //cout<<0;
        //return 0;
    //}
    for(int i=0;i<n-1;i++){
        cin>>u>>v>>w;
        drzewo[u].push_back(make_pair(v,w));
        drzewo[v].push_back(make_pair(u,w));
    }
    for(int i=1;i<=n;i++){
        bool dojscie[1005]={0};
        long long d2[1005]={0};
        dfs(dojscie,i,0,i,d2);
        if(koszty[i]<mini)
            mini=koszty[i];
            //cout<<mini<<endl;
    }
    cout<<mini<<endl;
    return 0;
}

