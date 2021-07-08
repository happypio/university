#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
vector<pair<int,int> >drzewo[10];
int dist[10];
priority_queue<pair<int,int> > lista;

void dijikstra(int x)
{
    lista.push(make_pair(0,x));
    dist[x]=0;
    while(!lista.empty()){
        int u=lista.top().second;
        lista.pop();
        for(int unsigned i=0;i<drzewo[u].size();i++){
            int v=drzewo[u][i].second,weight=-drzewo[u][i].first;
            if(dist[v]>dist[u]+weight){
                dist[v]=dist[u]+weight;
                lista.push(make_pair(-dist[v],v));
            }
        }
    }

}
int main()
{
    ios_base::sync_with_stdio(false);
    int u,v,w,source=0;
    for(int i=0;i<14;i++){
        dist[i]=INT_MAX;
        cin>>u>>v>>w;
        drzewo[u].push_back(make_pair(-w,v));
        drzewo[v].push_back(make_pair(- w,u));
    }
    dijikstra(source);
    for(int i=0;i<10;i++){
        cout<<i<<" "<<dist[i]<<endl;
    }
    return 0;
}
