#include<stdio.h>

int main(void)
{
    int m,n,t,licznik=0;
    scanf("%d %d %d",&m,&n,&t);

    for(int i=0;i<m;i++)
    {
        for(int w=0;w<(n/t);w++)
        {
            for(int j=0;j<t-(i%t);j++)
            {
                printf("#");
            }
            for(int z=0;z<(i%t);z++)
            printf(" ");
        }
            if((n%t)<(t-(i%t)))
                licznik=n%t;
            else
                licznik=t-(i%t);
            for(int j=0;j<licznik;j++)
            {
                printf("#");
            }

            for(int z=0;z<n%t-licznik;z++)
                printf(" ");

        printf("\n");
    }
    return 0;
}
