#include<stdio.h>
#define LL (long long int)1
int t[20],znalezione=0,n;
long long maska_maks1,maska_maks2,maska_maks3,maska_maks4;
void rekurencja(long long suma,int index,long long maska1,long long maska2,long long maska3,long long maska4,int znak)
{
    if(znalezione==1)
        return;
    if(index==n){
        if(suma==1){
            maska_maks1=maska1;
            maska_maks2=maska2;
            maska_maks3=maska3;
            maska_maks4=maska4;
            znalezione=1;
        }
        return;
    }
    //printf("%lld %d\n",suma,index);
    if(znak==0){
        suma=suma+t[index];
        maska1=maska1|(LL<<index);
    }
    if(znak==1){
        suma=suma-t[index];
        maska2=maska2|(LL<<index);
    }
    if(znak==2){
        suma=suma*t[index];
        maska3=maska3|(LL<<index);
    }
    if(znak==3&&t[index]!=0){
        suma=suma/t[index];
        maska4=maska4|(LL<<index);
    }
    if(znak==3&&t[index]==0)
        return;
    //printf("%lld %d\n",suma,index);
    for(int i=0;i<4;i++){
        if(i!=znak)
            rekurencja(suma,(index+1),maska1,maska2,maska3,maska4,i);
    }
    return;
}
int main(void)
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&t[i]);
    }
    long long suma=t[0],maska1=0,maska2=0,maska3=0,maska4=0;
        for(int i=0;i<4;i++){
            if(i==0){
                rekurencja(suma,1,maska1|(LL<<1),maska2,maska3,maska4,i);
            }
            if(i==1){
                rekurencja(suma,1,maska1,maska2|(LL<<1),maska3,maska4,i);
            }
            if(i==2){
                rekurencja(suma,1,maska1,maska2,maska3|(LL<<1),maska4,i);
            }
            if(i==3&&t[1]!=0){
                rekurencja(suma,1,maska1,maska2,maska3,maska4|(LL<<1),i);
            }
    }
    if(znalezione==0)
        printf("Nie da sie\n");
    else{
        printf("%d",t[0]);
        for(int i=1;i<n;i++){
            if(maska_maks1&(LL<<i))
                printf("+");
            if(maska_maks2&(LL<<i))
                printf("-");
            if(maska_maks3&(LL<<i))
                printf("*");
            if(maska_maks4&(LL<<i))
                printf("/");
            printf("%d",t[i]);
        }
    }
    return 0;
}
