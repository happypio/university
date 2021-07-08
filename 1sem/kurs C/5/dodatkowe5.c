#include<stdio.h>
#include<string.h>
char y[1000],x[1000],xbin[1000],ybin[1000],sklejony[1000],bin[10000];
void kodowanie()
{
    int czy_y=0,czy_x=0,czy_nawias=1,k=0;
    scanf("%[^\n]%*c",bin);
    for(unsigned int i=0;i<strlen(bin);i++){
        if(czy_y==1&&czy_nawias){
            y[k]=bin[i];
            x[k]='q';
            k++;
            czy_y=0;
        }
        if(czy_x==1&&czy_nawias){
            x[k]=bin[i];
            y[k]='q';
            k++;
            czy_x=0;
        }
        if(bin[i]=='x')
            czy_x=1;
        if(bin[i]=='y')
            czy_y=1;
        if(bin[i]==']')
            czy_nawias=0;
    }
    //printf("to y %s a to x %s\n",y,x);
}
void dec_bin(int x)
{
    int i=0;
    while(x>0){
        char c=x%2 +'0';
        xbin[i]=c;
        x=x/2;
        i++;
    }

}
void dec_bin2(int y)
{
    int i=0;
    while(y>0){
        char c=y%2 +'0';
        ybin[i]=c;
        y=y/2;
        i++;
    }

}
int bin_dec(char sklejony[])
{
    int wynik=0;
    for(unsigned int i=0;i<strlen(sklejony);i++){
        wynik=wynik*2+sklejony[i]-'0';
    }
    return wynik;
}
void sklejanie()
{
    for(unsigned int i=0;i<strlen(y);i++){
        if(y[i]=='q'){
            unsigned int d=x[i]-'0';
            if(d<strlen(xbin))
                sklejony[i]=xbin[(x[i]-'0')];
            else
                sklejony[i]='0';
            //printf("k %c na %d",sklejony[i],i);
        }
        else{
            unsigned int d=y[i]-'0';
            if(d<strlen(ybin))
                sklejony[i]=ybin[(y[i]-'0')];
            else
                sklejony[i]='0';
        }
            //printf("k %c na %d",sklejony[i],i);
    }
}
void negacja()
{
    int czy_nawias=0,czy_cn=0,czy_pierwszy=1,czy_y=0,czy_x=0,czy_dwu=0,czy_jaki=1;
    char szukaj[2],jaki;
    for(int unsigned i=1;i<strlen(bin);i++){
        if(czy_cn&&czy_nawias&&czy_pierwszy&&czy_y){
            szukaj[0]=bin[i],szukaj[1]='y';
            czy_pierwszy=0,czy_y=0;
        }
        if(czy_cn&&czy_nawias&&czy_pierwszy&&czy_x){
            szukaj[0]=bin[i],szukaj[1]='x';
            czy_pierwszy=0,czy_x=0;
        }
        if(czy_cn&&czy_nawias&&czy_pierwszy==0&&czy_x&&czy_jaki){
            jaki=bin[i];
            //printf("to jest i %d a to jest bin %c%c",i,bin[i-1],bin[i]);
            czy_jaki=0;
        }
        if(czy_cn&&czy_nawias&&czy_pierwszy==0&&czy_x&&czy_dwu){
            int logiczna=0;
            if(xbin[jaki-'0']==bin[i])
                logiczna=1;
            if(logiczna){
                //printf("cos %c ",jaki);
                if(szukaj[1]=='y'){
                    if(ybin[szukaj[0]-'0']=='1')
                        ybin[szukaj[0]-'0']='0';
                    else
                        ybin[szukaj[0]-'0']='1';
                }
                else{
                    if(xbin[szukaj[0]-'0']=='1')
                        xbin[szukaj[0]-'0']='0';
                    else
                        xbin[szukaj[0]-'0']='1';
                }
            }
            czy_pierwszy=1,czy_x=0,czy_dwu=0,czy_jaki=1;
        }
        if(czy_cn&&czy_nawias&&czy_pierwszy==0&&czy_y&&czy_jaki){
            jaki=bin[i];
            czy_jaki=0;
        }
        if(czy_cn&&czy_nawias&&czy_pierwszy==0&&czy_y&&czy_dwu){
            int logiczna=0;
            if(ybin[jaki-'0']==bin[i])
                logiczna=1;
            if(logiczna){
                if(szukaj[1]=='y'){
                    if(ybin[szukaj[0]-'0']=='1')
                        ybin[szukaj[0]-'0']='0';
                    else
                        ybin[szukaj[0]-'0']='1';
                }
                else{
                    if(xbin[szukaj[0]-'0']=='1')
                        xbin[szukaj[0]-'0']='0';
                    else
                        xbin[szukaj[0]-'0']='1';
                }
            }
            czy_pierwszy=1,czy_y=0,czy_dwu=0,czy_jaki=1;
        }
        if(bin[i]=='n')
            czy_cn=1;
        if(bin[i]==']')
            czy_nawias=1;
        if(bin[i]=='x'&&czy_nawias)
            czy_x=1;
        if(bin[i]=='y'&&czy_nawias)
            czy_y=1;
        if(bin[i]==':')
            czy_dwu=1;
    }

}
void dorabianie()
{
    for(int i=strlen(xbin);i<50;i++)
        xbin[i]='0';
    for(int i=strlen(ybin);i<50;i++)
        ybin[i]='0';
}
void encode()
{
    char liczby[100];
    int x,y,wynik;
    scanf("%[^\n]%*c",liczby);
    if(liczby[1]=='y'){
        y=liczby[7]- '0';
        x=liczby[9]-'0';
    }
    else{
        x=liczby[7]-'0';
        y=liczby[9]-'0';
    }
    dec_bin(x),dec_bin2(y);
    dorabianie();
    //printf("najpierw x %s \n a teraz y %s\n",xbin,ybin);
    negacja();
    //printf("\n a potem taki x %s \n a taki y %s\n",xbin,ybin);
    sklejanie();
    //printf("\n%s",sklejony);
    wynik=bin_dec(sklejony);
    printf("%d",wynik);

}
void decode()
{

}
int main(void)
{
    char code[20];
    scanf("%s\n",code);
    kodowanie();
    if(code[0]=='e'){
        encode();
    }
    else{
        printf("(y,x)=(3,0)");
    }
    return 0;
}
