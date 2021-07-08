#include<stdio.h>
int wynik=0;
int aktualny=0;
int poprzedni=0;
void licz(int c)
{
    for(int i=128;i>=1;i/=2){
        if((c/i)%2==1){
            if(poprzedni==0){
                aktualny++;
                if(aktualny>wynik)
                    wynik=aktualny;
            }
        }
        else{
            if(poprzedni==1){
                aktualny++;
                if(aktualny>wynik)
                    wynik=aktualny;
            }
            else
                aktualny=0;
        }
        //printf("jestem w %d %d \n",(c/i)%2,aktualny);
        poprzedni=(c/i)%2;
    }
}

int main(void)
{
    int teraz=0,c;
    while((c=getchar())!=EOF){
        //teraz=(c >> 7) & 1;
        teraz=(c/128)%2;
        if(poprzedni==teraz)
            aktualny=0;
        licz(c);
    }
    printf("%d",wynik);

    return 0;
}
