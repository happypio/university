#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,c1,c2,c3,cn;
    cin>>n;
    int a[n+1];
    cout<<"? 1 2"<<endl;
    fflush(stdout);
    cin>>c1;
    cout<<"? 1 3"<<endl;
    fflush(stdout);
    cin>>c2;
    cout<<"? 2 3"<<endl;
    fflush(stdout);
    cin>>c3;
    a[3]=(c3-c1+c2)/2;
    a[2]=(c3-a[3]);
    a[1]=(c2-a[3]);
    for(int i=4;i<=n;i++){
        cout<<"? "<<"1 "<<i<<endl;
        fflush(stdout);
        cin>>cn;
        a[i]=cn-a[1];
    }
    cout<<"! ";
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
    fflush(stdout);
    return 0;
}
