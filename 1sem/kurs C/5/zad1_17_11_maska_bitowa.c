#include<stdio.h>
#define LL (long long int)1
long long liczby[40],wynik_maska,maksi=0;
int n;
void rekurencja(long long liczby[40],int index,long long maska,int licznik)
{
    if (licznik>10||maksi==9)
        return;
    if(index==n){
        long long suma=0,j=0;
        for(int i=0;i<n;i++){
            if((LL<<i)&maska){
                //printf("%d ",i);
                suma+=liczby[i],j++;
            }
        }
        if(j>maksi&&suma==0){
            maksi=j;
            wynik_maska=maska;

        }
    }
    else{
        rekurencja(liczby,index+1,maska,licznik);
        maska=maska|(LL<<index),licznik++;
        rekurencja(liczby,index+1,maska,licznik);
    }
    return;

}
int main(void)
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%lld",&liczby[i]);
    rekurencja(liczby,0,0,0);
    for(int i=0;i<n;i++)
        if((LL<<i)&wynik_maska)
            printf("%lld ",liczby[i]);
    return 0;
}


/*long long x= (long long int )1<<61;
    printf("%lld\n",x);
    x=x|1;
    printf("%lld\n",x);
    printf("%lld",x&61);
    x=x|1<<2;
    x=x| 1<<5;
    for(int i=0;i<60;i++){
        if(((long long int)1<<i)&x)
            printf("%d",i);
    }*/
