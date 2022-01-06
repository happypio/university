#include<iostream>
#include<set>
using namespace std;
int n,x,y;
set<long long>wynik;
void wrzuc_set(long long lucky,int l){
    if(lucky>n||l>10)
        return;
    wynik.insert(lucky);
    wrzuc_set(lucky*10+x,l+1);
    wrzuc_set(lucky*10+y,l+1);
    return;
}
int main()
{
    cin>>n;
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            x=i,y=j;
            wrzuc_set(0,0);
        }
    }
    cout<<wynik.size()-1;
    return 0;
}
