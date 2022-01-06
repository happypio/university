#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int obraz[1100][1100];
int liczenie[1100][1100];
int wynik=1;
void w_prawo1(int j,int x)
{
    int aktualny =1;
    for(int i=1;i<x;i++){
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
void w_lewo1(int j,int x)
{
    int aktualny=1;
    for(int i=x-2;i>=0;i--){
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
void w_prawo(int i,int x)
{
    if(obraz[i-1][0]!=obraz[i][0])
        if(liczenie[i][0]<liczenie[i-1][0]+1)
            liczenie[i][0]=liczenie[i-1][0]+1;
    if(liczenie[i][0]>wynik)
            wynik=liczenie[i][0];
    for(int j=1;j<x;j++){

        if(obraz[i][j-1]!=obraz[i][j]){
            if(obraz[i-1][j]!=obraz[i][j]){//printf("(%d,%d) ",i,j);
                //printf(" %lld (%d,%d)\n",liczenie[i-1][j],i,j);
                if(liczenie[i][j-1]>liczenie[i-1][j]){
                    if(liczenie[i][j]<liczenie[i][j-1]+1)
                        liczenie[i][j]=liczenie[i][j-1]+1;}
                else{
                    if(liczenie[i][j]<liczenie[i-1][j]+1){
                        liczenie[i][j]=liczenie[i-1][j]+1;
                        }}
            }
            else{
                if(liczenie[i][j]<liczenie[i][j-1]+1)
                    liczenie[i][j]=liczenie[i][j-1]+1;}
        }
        else{
            if(obraz[i-1][j]!=obraz[i][j]){
                //printf(" %lld (%d,%d\n",liczenie[i-1][j],i,j);
                if(liczenie[i][j]<liczenie[i-1][j]+1)
                    liczenie[i][j]=liczenie[i-1][j]+1;
            }
        }
        if(liczenie[i][j]>wynik)
            wynik=liczenie[i][j];

    }
}
void w_lewo(int i,int x)
{
    int aktualny=1;
    if(obraz[i-1][x-1]!=obraz[i][x-1]){
        if(liczenie[i][x-1]<liczenie[i-1][x-1]+1)
            liczenie[i][x-1]=liczenie[i-1][x-1]+1;
        aktualny=liczenie[i-1][x-1]+1;}
    if(liczenie[i][x-1]>wynik)
            wynik=liczenie[i][x-1];
    for(int j=x-2;j>=0;j--){
        if(obraz[i][j+1]!=obraz[i][j]){
        aktualny++;
        if(aktualny>liczenie[i][j])
            liczenie[i][j]=aktualny;
        if(obraz[i-1][j]!=obraz[i][j]){
            if(liczenie[i-1][j]+1>aktualny)
                aktualny=liczenie[i-1][j]+1;
                if(aktualny>liczenie[i][j])
                    liczenie[i][j]=aktualny;
        }}
        else{
            aktualny=1;
            if(obraz[i-1][j]!=obraz[i][j]){
                if(liczenie[i-1][j]+1>aktualny)
                    aktualny=liczenie[i-1][j]+1;
                if(aktualny>liczenie[i][j])
                    liczenie[i][j]=aktualny;}
            }
        if(liczenie[i][j]>wynik)
            wynik=liczenie[i][j];
    }
}
void waz(int x,int y)
{
    w_prawo1(0,x);
    w_lewo1(0,x);
    for(int i=1;i<y;i++){
            //printf("\n%d\n",i);
            w_prawo(i,x);
            w_lewo(i,x);
    }
}

int main(void)
{
    char nic;
    int x,y;
    scanf("%c %c",&nic,&nic);
    scanf("%d %d",&x,&y);
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

    printf("%d\n",wynik);
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++)
            printf("%d ",liczenie[i][j]);
        printf("\n");
    }

    return 0;
}
