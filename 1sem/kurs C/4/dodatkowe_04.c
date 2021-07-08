#include<stdio.h>
int obraz[1030][1030];
long long liczenie[1030][1030];
long long wynik=1;
void w_prawo(int j,int i,long long aktualny,int x)
{
    for(;i<x;i++){
        if(obraz[j][i-1]!=obraz[j][i]){
            aktualny++;
            if(aktualny>liczenie[j][i])
                liczenie[j][i]=aktualny;
            if(liczenie[j][i]>wynik)
                wynik=liczenie[j][i];
        }
        else
            aktualny=1;
    }
}
void w_lewo(int j,int i,long long aktualny)
{
    for(;i>=0;i--){
        if(obraz[j][i+1]!=obraz[j][i]){
            aktualny++;
            if(aktualny>liczenie[j][i])
                liczenie[j][i]=aktualny;
            if(liczenie[j][i]>wynik)
                wynik=liczenie[j][i];
        }
        else
            aktualny=1;
    }
}
void waz(int x,int y)
{
    w_prawo(0,1,1,x);
    w_lewo(0,x-2,1);
    for(int i=1;i<y;i++){
        for(int j=0;j<x;j++){
            if(obraz[i-1][j]!=obraz[i][j]){
                    if(j<x-1)
                        w_prawo(i,j+1,liczenie[i-1][j]+1,x);
                    if(j>0)
                        w_lewo(i,j-1,liczenie[i-1][j]+1);
                    if(liczenie[i-1][j]+1>liczenie[i][j])
                        liczenie[i][j]=liczenie[i-1][j]+1;
                    if(liczenie[i][j]>wynik)
                        wynik=liczenie[i][j];
            }
            else{
                if(j<x-1)
                    w_prawo(i,j+1,1,x);
                if(j>0)
                    w_lewo(i,j-1,1);
            }
        }
    }
}
int main(void)
{
    char nic[2];
    int x,y;

    scanf("%s %d %d",nic,&x,&y);
    if(x==0||y==0){
        printf("0");
        return 0;
    }
    for(int i=0;i<y;i++)
        for(int j=0;j<x;j++){
            scanf("%d",&obraz[i][j]);
            liczenie[i][j]=1;
        }
    waz(x,y);

    printf("%lld\n",wynik);
    /*for(int i=0;i<y;i++){
        for(int j=0;j<x;j++)
            printf("%d ",liczenie[i][j]);
        printf("\n");
    }*/

    return 0;
}
