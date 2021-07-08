#include<iostream>
using namespace std;
int mieszkania[105][2],mozliwosci=0,l_mieszkania=0,m,n,pietro_temp=0,pietro,maksi_pietro=0;
void rekurencja(int f,int s,int k)
{
    if(mozliwosci>1)
        return;
    if(f>maksi_pietro){
        l_mieszkania=s;
        if(n%l_mieszkania==0)
            pietro_temp=n/l_mieszkania;
        else
            pietro_temp=n/l_mieszkania+1;
        if(pietro==0)
            pietro=pietro_temp;
        if(pietro!=pietro_temp||mozliwosci==0)
            mozliwosci++;
        //cout<<l_mieszkania<<endl;
        return;
    }
    if(mieszkania[f][0]!=0)
        if(k>=mieszkania[f][0])
            return;
    if(mieszkania[f][1]!=0)
        if(k+s<mieszkania[f][1])
            return;
    rekurencja(f+1,s,k+s);
}
int main()
{
    mieszkania[1][0]=1,mieszkania[1][1]=1;
    int f,k;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>k>>f;
        if(k>mieszkania[f][1])
            mieszkania[f][1]=k;
        if(k<mieszkania[f][0]&&mieszkania[f][0]!=0)
            mieszkania[f][0]=k;
        else
            if(mieszkania[f][0]==0)
                mieszkania[f][0]=k;
        if(maksi_pietro<f)
            maksi_pietro=f;
    }
    for(int i=100;i>0;i--){
        rekurencja(1,i,0);
    }
    if(mozliwosci>1||mozliwosci==0)
        cout<<-1<<endl;
    else
        cout<<pietro;
    return 0;
}
