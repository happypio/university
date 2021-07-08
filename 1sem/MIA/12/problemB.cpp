#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
using namespace std;
long long odleglosc[105],drogi[105],najkrotszy;
double wynik=1;
void bfs(vector<int> tab[],int x){
        queue<int> q;
        q.push(x);
        odleglosc[x]=0;
        drogi[x]=1;
        while(!q.empty())
        {
            x = q.front();
            q.pop();
            for(int unsigned i=0;i<tab[x].size();i++){
                if(odleglosc[tab[x][i]]>odleglosc[x]+1){
                        odleglosc[tab[x][i]]=odleglosc[x]+1;
                        drogi[tab[x][i]]=drogi[x];
                        q.push(tab[x][i]);
                }
                else{
                    if(odleglosc[tab[x][i]]==odleglosc[x]+1)
                        drogi[tab[x][i]]+=drogi[x];
                }
            }
        }
}
int main()
{
    for(int i=0;i<105;i++)
        odleglosc[i]=(1<<30);
    int m,n;
    cin>>n>>m;
    vector <int> drzewo[n+1];
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        drzewo[a].push_back(b);
        drzewo[b].push_back(a);
    }
    bfs(drzewo,1);
    najkrotszy=odleglosc[n];
    long long trasy=drogi[n];
    //cout<<najkrotszy<<" "<<trasy<<endl;
    for(int i=2;i<n;i++){
        for(int j=0;j<105;j++){
            odleglosc[j]=(1<<30);
            drogi[j]=0;
        }
        bfs(drzewo,i);
        if(odleglosc[1]+odleglosc[n]==najkrotszy){
            long long bezpieczne=2*(drogi[1]*drogi[n]);
            wynik=max(wynik,(double) bezpieczne/(double) trasy);
            //cout<<galezie
            //cout<<drogi[1]<<" "<<drogi[n]<<endl;
        }
    }
    cout<<setprecision(10)<<wynik;
    return 0;
}
