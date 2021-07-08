#include<stdio.h>
#include<ctype.h>
#include<math.h>
const int stala=10;
int tab[300],wszystkie_znaki=0;
void wypisz(int litera, int wystapienia)
{
    float z=wszystkie_znaki;
    float x=(wystapienia/z)*stala;
    int n=round(x),i=0;
    char t=litera;
    printf("%c [",t);
    for(;i<n;i++)
        printf("*");
    for(;i<stala;i++)
        printf(" ");
    printf("]");
}
int main(void)
{
    int c;
    while((c=getchar())!=EOF)
    {
        if(isgraph(c))
        {
            wszystkie_znaki++;
            tab[c]++;
        }
    }
    for(int i=0;i<256;i++)
    {
        if(tab[i]>0)
        {
            wypisz(i,tab[i]);
            printf("\n");
        }
    }

    return 0;
}
