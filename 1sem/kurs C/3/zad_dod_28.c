#include<stdio.h>
char format[10];
int bok,dlugosc_RR=1,dlugosc_RS=1,dlugosc_RD=1,obraz[1024][1024];

void wczytywanieRR(int bok)
{
    int k,parz=0;
    scanf("%d",&k);
    for(int i=0;i<bok;i++)
        for(int j=0;j<bok;j++)
        {
            if(k==0)
            {
                scanf("%d",&k);
                parz=((parz%2)+1)%2;
            }
            if(parz%2==0)
            {
                obraz[i][j]=0;
                k--;
            }
            else{
                obraz[i][j]=1;
                k--;
            }
        }
}

void wczytywanieRS(int bok)
{
    int k,parz=0;
    scanf("%d",&k);
    for(int i=0;i<bok;i++){
        if(i%2==0)
            for(int j=0;j<bok;j++){
                if(k==0){
                    scanf("%d",&k);
                    parz=((parz%2)+1)%2;
                }
                if(parz%2==0){
                    obraz[i][j]=0;
                    k--;
                }
                else{
                    obraz[i][j]=1;
                    k--;
                }
            }
        if(i%2==1)
            for(int j=bok-1;j>=0;j--){
                if(k==0){
                    scanf("%d",&k);
                    parz=((parz%2)+1)%2;
                }
                if(parz%2==0){
                    obraz[i][j]=0;
                    k--;
                }
                else{
                    obraz[i][j]=1;
                    k--;
                }
            }
        }

}

void wczytywanieRD(int bok)
{
    int k,parz=0;
    scanf("%d",&k);
        for(int i=0;i<bok;i++)
        if(i%2==0)
            for(int j=0;j<=i;j++)
            {
                if(k==0){
                    scanf("%d",&k);
                    parz=((parz%2)+1)%2;
                }
                if(parz%2==0){
                    obraz[i-j][j]=0;
                    k--;
                }
                else{
                    obraz[i-j][j]=1;
                    k--;
                }
            }
            else
            for(int j=i;j>=0;j--)
            {
                if(k==0){
                    scanf("%d",&k);
                    parz=((parz%2)+1)%2;
                }
                if(parz%2==0){
                    obraz[i-j][j]=0;
                    k--;
                }
                else{
                    obraz[i-j][j]=1;
                    k--;
                }
            }
    for(int i=bok-1;i>=0;i--)
        if(i%2==1)
            for(int j=0;j<i;j++){
                if(k==0){
                    scanf("%d",&k);
                    parz=((parz%2)+1)%2;
                }
                if(parz%2==0){
                    obraz[bok-1-j][bok-i+j]=0;
                    k--;
                }
                else{
                    obraz[bok-1-j][bok-i+j]=1;
                    k--;
                }
            }
        else
            for(int j=i-1;j>=0;j--){
                if(k==0){
                    scanf("%d",&k);
                    parz=((parz%2)+1)%2;
                }
                if(parz%2==0){
                    obraz[bok-1-j][bok-i+j]=0;
                    k--;
                }
                else{
                    obraz[bok-1-j][bok-i+j]=1;
                    k--;
                }
        }
}

void liczenieRR(int bok)
{
    int poprzednik=obraz[0][0];
    if(poprzednik==1)
        dlugosc_RR++;
    for(int i=0;i<bok;i++)
        for(int j=0;j<bok;j++)
        {
            if(poprzednik!=obraz[i][j])
            {
                poprzednik=obraz[i][j];
                dlugosc_RR++;
            }
        }
}

void liczenieRS(int bok)
{
    int poprzednik=obraz[0][0];
    if(poprzednik==1)
        dlugosc_RS++;
    for(int i=0;i<bok;i++){
        if(i%2==0)
            for(int j=0;j<bok;j++){
                if(poprzednik!=obraz[i][j]){
                    poprzednik=obraz[i][j];
                    dlugosc_RS++;
                }
            }
        if(i%2==1)
            for(int j=bok-1;j>=0;j--){
                if(poprzednik!=obraz[i][j]){
                    poprzednik=obraz[i][j];
                    dlugosc_RS++;
                }

            }
        }

}
void liczenieRD(int bok)
{
    int poprzednik=obraz[0][0];
    if(poprzednik==1)
        dlugosc_RD++;
    for(int i=0;i<bok;i++)
        if(i%2==0)
            for(int j=0;j<=i;j++){
                if(poprzednik!=obraz[i-j][j]){
                    poprzednik=obraz[i-j][j];
                    dlugosc_RD++;
                }
            }
        else
            for(int j=i;j>=0;j--)
              if(poprzednik!=obraz[i-j][j]){
                    poprzednik=obraz[i-j][j];
                    dlugosc_RD++;
            }
    for(int i=bok-1;i>=0;i--)
        if(i%2==1)
            for(int j=0;j<i;j++){
                if(poprzednik!=obraz[bok-1-j][bok-i+j]){
                    poprzednik=obraz[bok-1-j][bok-i+j];
                    dlugosc_RD++;
                }
            }
        else
            for(int j=i-1;j>=0;j--){
               if(poprzednik!=obraz[bok-1-j][bok-i+j]){
                    poprzednik=obraz[bok-1-j][bok-i+j];
                    dlugosc_RD++;
                }
        }
}
int main(void)
{
    char format[10];
    scanf("%s",format);
    if(format[0]=='P'){
        scanf("%d %d",&bok,&bok);
        for(int i=0;i<bok;i++)
            for(int j=0;j<bok;j++)
                scanf("%d",&obraz[i][j]);
    }
    else
    {
        scanf("%d",&bok);
        if(format[1]=='R')
            wczytywanieRR(bok);
        if(format[1]=='S')
            wczytywanieRS(bok);
        if(format[1]=='D')
            wczytywanieRD(bok);
    }

    /*for(int i=0;i<bok;i++){
        for(int j=0;j<bok;j++)
            printf("%d ",obraz[i][j]);
        printf("\n");
    }*/
    if(bok==0){
        printf("2 2 2");
        return 0;
    }
    else{
        liczenieRD(bok);
        liczenieRR(bok);
        liczenieRS(bok);
    }
    printf("%d %d %d",dlugosc_RR,dlugosc_RS,dlugosc_RD);

    return 0;
}
