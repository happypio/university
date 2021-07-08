#include<stdio.h>
#include<stdbool.h>
#include <math.h>

bool czy_pierwsza(int x)
{
    if (x==2)
        return 1;
    if(x%2==0)
        return 0;
    for(int i=3;i*i<=x;i=i+2)
        if(x%i==0)
         return 0;
    return 1;
}

double dzielenie(int m,int n)
{
        for(int i=2;;i++)
    {
        if(czy_pierwsza(i))
            if(m%i!=n%i)
                return i;
    }

}

int main(void)
{
    int m,n,m1,m2;
    double maksi2=dzielenie(2,3)/log(3);
    scanf("%d %d",&m,&n);
    printf("wynik to %lf \n",dzielenie(m,n));

    for(int i=3;i<=1000;i++)
        for(int j=i+1;j<=1000;j++)
        {
            int z=dzielenie(i,j);
            double maks=z/log(j);
            if(maksi2<maks)
            {
                maksi2=maks;
                m1=i;
                m2=j;
            }


        }

    printf("%lf a para liczb to %d %d",maksi2,m1,m2);



    return 0;
}
