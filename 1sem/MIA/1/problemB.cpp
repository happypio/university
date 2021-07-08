#include<iostream>
using namespace std;

int main()
{
int k;
cin>>k;
long long int n,m,x1,y1,x2,y2;
while(k>0)
{
	cin>>n>>m>>x1>>y1>>x2>>y2;
	long long min_dol=min(m-y1,m-y2);
	long long min_gora=min(y1-1,y2-1);
	long long min_prawo=min(n-x1,n-x2);
	long long min_lewo=min(x1-1,x2-1);
	long long x=min_lewo+min_prawo+1;
	long long y=min_dol+min_gora+1;
    long long suma2,suma=x*y*2;
	long long dodatk_x=2*x-n,dodatk_y=2*y-m;
	if(dodatk_x<0 or dodatk_y<0)
        suma2=0;
    else
        suma2=dodatk_x*dodatk_y;
    long long wynik=n*m-suma+suma2;
	cout<<wynik<<endl;

	k--;
}
return 0;
}
