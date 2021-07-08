#include<stdio.h>
#include<string.h>
int bloki[8][10][10];
int wymiary[8][2];
int wynik_maks=0,m,n,nb,nt;
int min(int a,int b){
    if(a>b)
        return b;
    else
        return a;
}
void zamaluj (int plansza[10][10],int blok,int sz,int h)
{
    for(int i=h;i<h+wymiary[blok][1];i++){
        for(int j=sz;j<sz+wymiary[blok][0];j++){
            if(plansza[i][j]!=0){
                plansza[i][j]=bloki[blok][j-sz][i-h];
            }
        }
    }
}
void wrzucanie(int kolejnosc[]){
    int plansza[10][10]={0};
    for(int i=0;i<nb;i++){
        for(int j=0;j<m;j++){
            if(wymiary[kolejnosc[i]][0]+j<=m)
                for(int h=0;h<n;h++){
                    for(int k=0;k<min(h,wymiary[kolejnosc[i]][1]);k++)
                        for(int l=0;l<wymiary[kolejnosc[i]][0];l++){
                            if(bloki[kolejnosc[i]][k][l]!=plansza[h-k][m+l]){
                                if(k>=h)
                                    zamaluj(plansza,kolejnosc[i],m,h-1);
                            }
                        }
                }
            }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            printf("%d ",plansza[i][j]);
        printf("\n");
    }
}
int main(void)
{
    char c[10];
    scanf("%d %d %d",&m,&n,&nb);
    for(int i=0;i<nb;i++){
        scanf("%d %d",&wymiary[i][0],&wymiary[i][1]);
        for(int j=0;j<wymiary[i][1];j++){
                scanf("%s",c);
                for(int unsigned z=0;z<strlen(c);z++){
                    if(c[z]=='#')
                        bloki[i][j][z]=1;
                    else
                        bloki[i][j][z]=0;
                }
            }
    }
    scanf("%d",&nt);
    for(int i=0;i<nt;i++){
        int kolejnosc[nb];
        for(int j=0;j<nb;j++)
            scanf("%d",&kolejnosc[j]);
        wrzucanie(kolejnosc);
    }
    printf("%d",wynik_maks);
    return 0;
}
