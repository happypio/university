#include<stdio.h>
#include<stdbool.h>
#define LL (long long int)1
int m,n,bloki,testy,ntest[12],maksi=0;
long long maska_maks=0;
bool wypisywanie=0,koncowa_plansza=0,blad=0;
struct blok{
    int w;
    int h;
    int t[10][10];
};
struct blok bloczek[12];
void zerowanie()
{
    for (int i=0;i<12;i++){
        bloczek[i].w=0;
        bloczek[i].h=0;
    }
}
void input()
{
    int w,h;
    char c;
    if(scanf("%d %d %d",&m,&n,&bloki)){};
    for(int i=0;i<bloki;i++){
       if(scanf("%d %d",&w,&h)){};
       bloczek[i].w=w,bloczek[i].h=h;
        for(int j=0;j<h;j++){
            for(int k=0;k<w;k++){
                c=getchar();

                if(c=='#'){
                    bloczek[i].t[j][k]=1;}
                else{
                    if(c=='.'){
                        bloczek[i].t[j][k]=0;}
                        else
                            k--;
                }
            }
       }
    }
    if(scanf("%d",&testy)){};
}
long long potega10(int n){
    long long wynik=1;
    for(int i=1;i<=n;i++)
        wynik=wynik*10;
    return wynik;
}
int min(int a,int b)
{
    if(a>b)
        return b;
    return a;
}
void zamaluj(int pozycja,int blok,int plansza[10][10],int koniec){
    for(int i=bloczek[blok].h-1;i>=0;i--){
        for(int j=0;j<bloczek[blok].w;j++){
            if(bloczek[blok].t[i][j]==1)
                plansza[koniec][pozycja+j]=bloczek[blok].t[i][j];
        }
        koniec--;
    }
    if(wypisywanie) printf("%d %d\n",pozycja,blok);
    if(wypisywanie)
    for(int k=0;k<10;k++){
        for(int g=0;g<10;g++)
            printf("%d ",plansza[k][g]);
        printf("\n");
    }
}
int wrzuc(int pozycja,int blok,int plansza[10][10])
{
    if(bloczek[blok].h>n||bloczek[blok].w+pozycja>m)
        return 1;
    for(int i=0;i<n;i++){
        for(int j=0;j<bloczek[blok].w;j++){
            for(int k=0;k<=min(i,bloczek[blok].h-1);k++){
                if(i-k<0||pozycja+j>m){
                    //printf("i-k = %d - %d ; pozycja+j= %d %d m=%d \n a blok= %d",i,k,pozycja,j,m,blok);
                    return 1;
                }
                if(plansza[i-k][pozycja+j]==1&&bloczek[blok].t[bloczek[blok].h-1-k][j]){
                    if(bloczek[blok].h>i){
                        return 1;}
                    else{
                        zamaluj(pozycja,blok,plansza,i-1);
                        return 0;}}
            }
            //printf("kukuryku");
        }
    }
    if(wypisywanie) printf("WRZUCANIE %d %d\n",pozycja,blok);
    if(n-1>=0)
    zamaluj(pozycja,blok,plansza,n-1);
    return 0;
}
int wrzucanie(long long maska)
{
    int plansza[10][10]={0};
    int wynik=0,i=0;
    for(;i<bloki;i++){
        long long pozycja=(maska/(potega10(ntest[i])))%10;
        //if(wypisywanie) printf("%d %d\n",pozycja,ntest[i]);
        if(wrzuc(pozycja,ntest[i],plansza))
            i=10;
    }
    if(i>=10)
        return wynik;
    //if(koncowa_plansza)
    //for(int k=0;k<10;k++){
        //for(int g=0;g<10;g++)
            //printf("%d ",plansza[k][g]);
        //printf("\n");
    //}
    int suma=0;
    for(int k=0;k<n;k++){
        for(int j=0;j<m;j++){
            if(plansza[k][j]==1)
            suma++;
        }
        if(suma==m)
            wynik++;
        suma=0;
    }
    return wynik;
}
void tetris(long long index,int nblok,long long maska,int i)
{
    //printf("%lld\n",maska);
    if(i<bloki)
        if((bloczek[nblok].w+index>m || bloczek[nblok].h>n))
            return;
    if(i>=bloki){
        //printf("%lld ",maska);
        int tmp=wrzucanie(maska);
        if(tmp>maksi){
            maksi=tmp;
            maska_maks=maska;
        }
        //printf("%d\n",tmp);
        return;
    }
    if(bloczek[nblok].w+index<m)
        tetris(index+1,nblok,maska,i);
    tetris(0,ntest[i+1],maska+index*potega10(nblok),i+1);
    return;
}
int main(void)
{
    zerowanie();
    input();
    for(int i=0;i<testy;i++){
        for(int j=0;j<bloki;j++)
            if(scanf("%d",&ntest[j])){};
        tetris(0,ntest[0],potega10(12),0);
        printf("%d oraz maska %lld\n",maksi,maska_maks);
        maksi=0;
    }




    /*for(int i=0;i<bloki;i++){
       for(int j=0;j<bloczek[i].h;j++){
            for(int k=0;k<bloczek[i].w;k++){
                printf("%d ",bloczek[i].t[j][k]);
            }
            printf("\n");
       }
    }*/
    return 0;
}



