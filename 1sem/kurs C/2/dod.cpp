#include<iostream>
#include<cmath>
using namespace std;

int przeksztalcanie(string klucz_tekst, int klucz[])
{
    int r=0;
    do{
        if(klucz_tekst[r]==',')
            klucz[r]=63;
        if(klucz_tekst[r]==' ')//lub 32
            klucz[r]=62;
        if(klucz_tekst[r]=='0')
            klucz[r]=-1;
        if(klucz_tekst[r]>'0'&&klucz_tekst[r]<='9')
            klucz[r]=klucz_tekst[r]-'0';
            else
            {
                if(klucz_tekst[r]>='A'&&klucz_tekst[r]<='Z')
                    klucz[r]=10 + klucz_tekst[r]-'A';
                else
                    if(klucz_tekst[r]>='a'&&klucz_tekst[r]<='b')
                        klucz[r]=36 + klucz_tekst[r]-'a';
            }

        r++;
    }while(r<klucz_tekst.size());
    return r-1;
}

void permutacja(int perm[],int klucz[],string klucz_tekst,int rozmiar)
{
    int i=0;
    do{
        klucz[i]=perm[klucz[i%rozmiar]];
        i++;
    }while(i<klucz_tekst.size());
}

void szyfrowanie(int tekst[],int klucz[],int wynik[],string klucz_tekst)
{
    int i=0;
    do{
        wynik[i]=(klucz[i]+tekst[i])%64;
        i++;
    }while(i<klucz_tekst.size());
}

void odszyfrowanie(int tekst[],int klucz[],int wynik[],string klucz_tekst)
{
    int i=0;
    do{
        wynik[i]=abs((tekst[i]-klucz[i]%64)%64);
        i++;
    }while(i<klucz_tekst.size());
}

void wypisanie(int wynik[])
{
    int i=0;
    do{
        if(wynik[i]==63)
            cout<<(",");
        else
        if(wynik[i]==62)//lub 32
            cout<<(" ");
        else
        if(wynik[i]==(-1))
            cout<<("0");
        else
        if(wynik[i]>0&&wynik[i]<=9)
            cout<<wynik[i];
            else
            {
                if(wynik[i]>=10&&wynik[i]<=35)
                {
                    char c='A'+wynik[i]-10;
                    cout<<c;
                }
                else
                    if(wynik[i]>=36&&wynik[i]<=61)
                    {
                        char c='a' +wynik[i]-36;
                        cout<<c;
                    }
            }
        i++;
    }while(wynik[i]!=0);
}
int main(void)
{
    int perm[64],klucz[260]={0},tekst[260]={0},wynik[260]={0};
    string operacja,klucz_tekst,tekst_pocz;
    cin>>operacja;
    for(int i=0;i<64;i++)
        cin>>perm[i];
    cin>>klucz_tekst;
    cin>>tekst_pocz;
    cout<<" "<<tekst_pocz;
    int rozmiar = przeksztalcanie(klucz_tekst,klucz);
    przeksztalcanie(tekst_pocz,tekst);
    permutacja(perm,klucz,klucz_tekst,rozmiar);

    if(operacja[0]=='e')
        szyfrowanie(tekst,klucz,wynik,klucz_tekst);
    else
        odszyfrowanie(tekst,klucz,wynik,klucz_tekst);

    wypisanie(wynik);
    cout<<tekst_pocz[5];

    return 0;
}
