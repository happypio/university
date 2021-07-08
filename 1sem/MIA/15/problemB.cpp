#include<iostream>
#include<set>
using namespace std;
#define LL (long long int)1
int main()
{
    long long numer,a,b,numer2;
    cin>>a>>b;
    set <long long> secik;
    for(int i=2;i<=60;i++){
            numer=(LL<<i)-1-(LL<<(i-2));
            //if(numer>b)
                //i=20;
            //else{
                numer2=numer;
                for(int j=i;j<=60;j++){
                    if(numer2>=a&&numer2<=b)
                        secik.insert(numer2);
                        numer2=numer2 +(LL<<(j));
                        //if(numer2>b)
                            //j=20;
                //}
                }
    }
    cout<<secik.size();
    return 0;
}
