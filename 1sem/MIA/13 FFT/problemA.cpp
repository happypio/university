#include<iostream>
#include<bits/stdc++.h>
using namespace std;
typedef complex<double> zespo;
const double PI = acos(-1);
void FFT(bool odczyt,vector<zespo> &wielomian) {
    int n=wielomian.size();
    if (n==1)
        return;

    vector<zespo> wielomian0(n/2),wielomian1(n/2);
    for (int i=0;2*i<n;i++){
        wielomian0[i]=wielomian[2*i];
        wielomian1[i]=wielomian[2*i+1];
    }
    FFT(odczyt,wielomian0);
    FFT(odczyt,wielomian1);

    double dzielnik;
    if(odczyt)
        dzielnik=-1;
    else
        dzielnik=1;
    double kat=2*PI/n*dzielnik;
    zespo w(1),wn(cos(kat),sin(kat));
    for (int i=0;2*i<n;i++){
        wielomian[i]=wielomian0[i]+w*wielomian1[i];
        wielomian[i+n/2]=wielomian0[i]-w*wielomian1[i];
        if (odczyt){
            wielomian[i]/=2;
            wielomian[i+n/2]/=2;
        }
        w=w*wn;
    }
    return;
}
vector<long long> mnozenie(vector<long long> const &a, vector<long long> const &b) {
    vector<zespo> wielomiana(a.begin(), a.end()), wielomianb(b.begin(), b.end());
    long long unsigned n=1;
    while (n<a.size()+b.size())
        n<<=1;
    wielomiana.resize(n);
    wielomianb.resize(n);

    FFT(0,wielomiana);
    FFT(0,wielomianb);
    for (int unsigned i=0;i<n;i++)
        wielomiana[i]*=wielomianb[i];
    FFT(1,wielomiana);
    vector<long long> wynik(n);
    for (int unsigned i=0;i<n;i++)
        wynik[i]=(round(wielomiana[i].real()));
    return wynik;
}
int main()
{
    int t,d,a;
    cin>>t;
    while(t>0){
        vector<long long> w1,w2;
        cin>>d;
        for(int i=0;i<=d;i++){
            cin>>a;
            w1.push_back(a);
        }
        for(int i=0;i<=d;i++){
            cin>>a;
            w2.push_back(a);
        }
        vector<long long>wynik=mnozenie(w1,w2);
        for(int i=0;i<(2*d)+1;i++)
            cout<<wynik[i]<<" ";
        cout<<endl;
        t--;
    }
    return 0;
}
