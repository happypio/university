#include<stdio.h>
#include<limits.h>
const int maksi=INT_MAX;
long long suma_dzielnik(int x)
{
    long long suma=1,k;
    for(int i=2;i*i<x;i++)
    {
        if(x%i==0)
            suma=suma+i+x/i;
        if(suma>maksi)
            return 0;
        k=i;
    }
    if((k+1)*(k+1)==x)
        suma=suma+k+1;
    if (suma>maksi)
        return 0;
    return suma;
}

int main(void)
{
    int s,dzielniki,dzielniki2=0,i;
    scanf("%d",&s);
    i=s+1;
    while(i>0)
    {
        dzielniki=suma_dzielnik(i);
            if(dzielniki==0)
        {
            printf("BRAK \n");
            return 0;
        }

        if(dzielniki>s)
        {
            dzielniki2=suma_dzielnik(dzielniki);

            if(i==dzielniki2&&i!=dzielniki)
            {
                printf("%d %d \n",i,dzielniki);
                return 0;
            }
        }
        i++;
    }
    return 0;
}
