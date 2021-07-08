#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int staly_klucz[260]={0};

int przeksztalcanie1(char klucz_tekst[], int klucz[])
{
    int r=0;
    do{
        if(klucz_tekst[r]==',')
        {
            klucz[r]=63;
        }
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
                    if(klucz_tekst[r]>='a'&&klucz_tekst[r]<='z')
                        klucz[r]=36 + klucz_tekst[r]-'a';
            }

        //printf("jestem w tym znaku %d a przeksztalcam z %c na %d\n",r,klucz_tekst[r],klucz[r]);
        staly_klucz[r]=klucz[r];
        if (klucz[r]==0)
            return -5;
        r++;
    }while(klucz_tekst[r]!=0);
    return r-1;
}

int przeksztalcanie2(char klucz_tekst[], int klucz[])
{
    int r=0;
    do{
        if(klucz_tekst[r]==',')
        {
            klucz[r]=63;
        }
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
                    if(klucz_tekst[r]>='a'&&klucz_tekst[r]<='z')
                        klucz[r]=36 + klucz_tekst[r]-'a';
            }

        //printf("jestem w tym znaku %d a przeksztalcam z %c na %d\n",r,klucz_tekst[r],klucz[r]);
        if(klucz[r]==0)
            return -5;
        r++;
    }while(klucz_tekst[r]!=0);
    return r-1;
}

void permutacja(int perm[],int klucz[],int tekst[],int rozmiar)
{
    int i=0;
    do{
        if(staly_klucz[i%(rozmiar+1)]==-1)
            staly_klucz[i%(rozmiar+1)]=0;

        klucz[i]=perm[staly_klucz[i%(rozmiar+1)]];
        //printf("klucz wynosi %d w tym miejscu %d stalykl %d\n",klucz[i],i,staly_klucz[i%(rozmiar+1)]);
        if(staly_klucz[i%(rozmiar+1)]==0)
            staly_klucz[i%(rozmiar+1)]=-1;
        i++;
    }while(tekst[i]!=0);
}

void szyfrowanie(int tekst[],int klucz[],int wynik[])
{
    int i=0;
    do{
        if(klucz[i]==-1)
            klucz[i]=0;
        if(tekst[i]==-1)
            tekst[i]=0;
        wynik[i]=(klucz[i]+tekst[i])%64;
        if(wynik[i]==0)
            wynik[i]=-1;
        //printf("zaszyfrowany %d w tym miejscu %d\n",klucz[i],i);
        if(klucz[i]==0)
            klucz[i]=-1;
        if(tekst[i]==0)
            tekst[i]=-1;
        i++;
    }while(tekst[i]!=0);
}

void odwracanie(int klucz[])
{
    int i=0;
    do{
        if(klucz[i]==-1)
        klucz[i]=0;
        klucz[i]=(64-klucz[i])%64;
        //printf("zaszyfrowany odwrocony %d w tym miejscu %d\n",klucz[i],i);
        if(klucz[i]==0)
        klucz[i]=-1;
        i++;
    }while(klucz[i]!=0);
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
        if(wynik[i]==(-1))
            printf("0");
        else
        if(wynik[i]>0&&wynik[i]<=9)
            printf("%d",wynik[i]);
            else
            {
                if(wynik[i]>=10&&wynik[i]<=35)
                    printf("%c",'A'+wynik[i]-10);
                else
                    if(wynik[i]>=36&&wynik[i]<=61)
                        printf("%c",'a'+wynik[i]-36);
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

    scanf("\n");
    scanf("%[^\n]%*c",klucz_tekst);
    //scanf("\n");
    scanf ("%[^\n]%*c",tekst_pocz);
    //printf("kupa%s",tekst_pocz);

    int rozmiar = przeksztalcanie1(klucz_tekst,klucz);
    int rozmiar2=przeksztalcanie2(tekst_pocz,tekst);
    if(rozmiar==-5 || rozmiar2==-5)
       {
           printf("UNSUPPORTED_ALPHABET\n");
           return 0;
       }

    permutacja(perm,klucz,tekst,rozmiar);

    szyfrowanie(tekst,klucz,wynik);
    if(operacja[0]=='d')
        odwracanie(klucz);
    szyfrowanie(tekst,klucz,wynik);
    wypisanie(wynik);
    printf("\n");
    return 0;
}
