#include<iostream>
#include<algorithm>
using namespace std;
long long seq[500005],pomoc[500005],dzielnik;
long long gcd(long long a, long long b)
{
    if (b)
        return gcd(b, a % b);
    else
        return a;
}

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>seq[i];
    long long temp[n],temp2;
    int sum=0,elem=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<elem;j++){
            temp2=gcd(seq[i],temp[j]);
            if(temp[j]!=temp2){
                pomoc[sum]=temp[j];
                temp[j]=temp2;
                sum++;
            }
        }
        temp[elem]=seq[i];
        elem++;
        sort(temp,temp+elem);
        elem=unique(temp,temp+elem)-temp;
    }
    for(int i=0;i<elem;i++){
        pomoc[sum]=temp[i];
        sum++;
    }
    sort(pomoc,pomoc+sum);
    cout<<unique(pomoc,pomoc+sum)-pomoc;
    return 0;
}

