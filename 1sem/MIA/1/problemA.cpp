#include<iostream>
using namespace std;

int main()
{
int n,s;
	cin>>n;
int t[n];
for(int i=0;i<n;i++)
{
	cin>>t[i];
}
int wynik=0;
for(int i=1;i<n;i++)
{
	for(int j=i-1;j>=0;j--)
	{
		if(t[j]>t[i])
		{
			wynik++;
		}
	}
}

cout<<wynik;
return 0;
}
