#include<iostream>
using namespace std;

void sortowanie (int n,int t[])
{
    for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
		if(t[j-1]>t[j])
			swap(t[j-1], t[j]);

}
int main()
{
    int n;
    cin>>n;
    int t[n];
    for(int i=0;i<n;i++)
        cin>>t[i];
    sortowanie(n,t);
    int a=0,b=0;
    if(n%2==0)
        for(int i=0;i<n;i=i+2)
    {
       a=a+t[i+1];
       b=b+t[i];
    }
    else
    {
        int i=0;
          for(i;i<n-1;i=i+2)
    {
       a=a+t[i];
       b=b+t[i+1];
    }
        a=a+t[i];
    }
    cout<<a<<" "<<b;

    return 0;
}
