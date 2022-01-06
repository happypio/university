#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
vector<pair<long long,int> >drzewo[1005];
priority_queue<pair<long long,int> > lista;
priority_queue<pair<long long, int> > lista2;
long long dist[1005][1005],taxi[1005],cena[1005],nowe[1005][1005],dist2[1005];
int n,m,x,y;

void dijikstra(int x)
{
    lista.push(make_pair(0,x));
    dist[x][x]=0;
    while(!lista.empty()){
        int u=lista.top().second;
        lista.pop();
        for(int unsigned i=0;i<drzewo[u].size();i++){
            int v=drzewo[u][i].second,weight=-drzewo[u][i].first;
            if(dist[x][v]>dist[x][u]+weight){
                dist[x][v]=dist[x][u]+weight;
                lista.push(make_pair(-dist[x][v],v));
            }
        }
    }

}
void dijikstra2(int x)
{
    lista2.push(make_pair(0,x));
    dist2[x]=0;
    while(!lista2.empty()){
        int u=lista2.top().second;
        lista2.pop();
        for(int unsigned i=0;i<drzewo[u].size();i++){//zrobily sie nowe wierzcholki ktore pomijaja inne przez co muismy uzyc drzewa cyk cyk;
                long long v=drzewo[u][i].second,weight=nowe[u][v];
                if(nowe[u][v]!=9223372036854775807){
                if(dist2[v]>dist2[u]+weight){
                    dist2[v]=dist2[u]+weight;
                    lista2.push(make_pair(-dist2[v],v));
            }
        }
        }
    }

}
int main()
{
    ios_base::sync_with_stdio(false);
    int u,v,w;
    cin>>n>>m>>x>>y;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        drzewo[u].push_back(make_pair(-w,v));
        drzewo[v].push_back(make_pair(-w,u));
    }
    for(int i=1;i<=n;i++){
        cin>>u>>v;
        taxi[i]=u;
        cena[i]=v;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            dist[i][j]=9223372036854775807;
            dist2[i]=9223372036854775807;
        }

    for(int i=1;i<=n;i++)
        dijikstra(i);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<dist[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(taxi[i]>=dist[i][j]&&i!=j)
                nowe[i][j]=cena[i];
            else
                nowe[i][j]=9223372036854775807;
        }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<nowe[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    dijikstra2(x);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<nowe[i][j]<<" ";
        cout<<endl;
    }
    if(dist2[y]==9223372036854775807)
        cout<<-1;
    else
        cout<<dist2[y];

    return 0;
}
