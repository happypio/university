#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int przeksztalcanie(char klucz_tekst[], int klucz[])
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
    }while(klucz_tekst[r]!=0);
    return r-1;
}

void permutacja(int perm[],int klucz[],int tekst[],int rozmiar)
{
    int i=0;
    do{
        klucz[i]=perm[klucz[i%rozmiar]];
        i++;
    }while(tekst[i]!=0);
}

void szyfrowanie(int tekst[],int klucz[],int wynik[])
{
    int i=0;
    do{
        wynik[i]=(klucz[i]+tekst[i])%64;
        i++;
    }while(tekst[i]!=0);
}

void odszyfrowanie(int tekst[],int klucz[],int wynik[])
{
    int i=0;
    do{
        wynik[i]=abs((tekst[i]-klucz[i]%64)%64);
        i++;
    }while(tekst[i]!=0);
}

void wypisanie(int wynik[])
{
    int i=0;
    do{
        if(wynik[i]==63)
            printf(",");
        else
        if(wynik[i]==62)//lub 32
            printf(" ");
        else
        if(wynik[i]==-1)
            printf("0");
        else
        if(wynik[i]>0&&wynik[i]<=9)
            printf("%d ",wynik[i]);
            else
            {
                if(wynik[i]>=10&&wynik[i]<=35)
                    printf("%c",'A'-wynik[i]);
                else
                    if(wynik[i]>=36&&wynik[i]<=61)
                        printf("%c",'a'-wynik[i]);
            }
        i++;
    }while(wynik[i]!=0);
}
int main(void)
{
    int perm[64],klucz[260]={0},tekst[260]={0},wynik[260]={0};
    char operacja[10]={0},klucz_tekst[260]={0},tekst_pocz[260]={0};
    scanf("%s",operacja);
    for(int i=0;i<64;i++)
        scanf("%d",&perm[i]);
    scanf("%s",klucz_tekst);
    scanf ("%s",tekst_pocz);
    int rozmiar = przeksztalcanie(klucz_tekst,klucz);
    przeksztalcanie(tekst_pocz,tekst);
    permutacja(perm,klucz,tekst,rozmiar);

    if(operacja[0]=='e')
        szyfrowanie(tekst,klucz,wynik);
    else
        odszyfrowanie(tekst,klucz,wynik);

    wypisanie(wynik);

    return 0;
}

