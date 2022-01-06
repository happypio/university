#include<iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    long double m,n,ax,ay,bx,by,wynik,mini;
    long double x1,x2,r;
    long double pi=3.14159265;
    cin>>m>>n>>r>>ax>>ay>>bx>>by;
    x1=(abs(ay-by)*r)/n;
    if(by>ay)
        mini=ay;
    else
        mini=by;
    x2=(abs(ax-bx)/m)*pi*r*(mini/n);
    long double wyni;
    if(x2>2*r*(mini/n))
        wyni=x1+(2*r*(mini/n));
    else
        wyni=x1+x2;
    cout.precision(15);
    cout<<wyni<<endl;


    return 0;
}
