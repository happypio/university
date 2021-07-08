#include<stdio.h>
#include<math.h>
#include<string.h>
double promien =10;
char t[21][21];
int main()
{
    char c[5];
    int h=0,m=0;
    printf("Prosze podac godzine w formacie hh:mm\n");
    scanf("%s",c);
    if(strlen(c)==5){
        if(c[0]==0)
            h=c[1]-'0';
        else
            h=(c[0]-'0')*10 + c[1]-'0';
        m=(c[3]-'0')*10 + (c[4]-'0');
    }
    else{
        h=c[0]-'0';
        m=(c[2]-'0')*10 + (c[3]-'0');
    }
    double costam=h%12;
    double godz=(costam/12)*2*3.1415926535897,sinusg=sin(godz),cosinusg=cos(godz);
    costam=m%12;
    double min=(costam/12)*2*3.1415926535897,sinusm=sin(min),cosinusm=cos(min);
    //printf("%lf",sinusg);
    int i=0,j=0;
    for(double y=-promien;y<=promien;y++){
        for(double x=-promien;x<=promien;x++){
                if((x*x + y*y)<=promien*promien){
                    t[i][j]='.';
                    j++;
                }
                else{
                    t[i][j]=' ';
                    j++;
                }
        }
            j=0;
            i++;
    }
    for(int i=0;i<21;i++){
        for(int j=0;j<21;j++)
            printf("%c",t[i][j]);
    printf("\n");
    }
    i=0,j=0;
    for(int i=1;i<=promien;i++)
        for(double y=-i;y<=i;y++){
        for(double x=-i;x<=i;x++){
                if((x*x + y*y)<=i*i)
                    printf(".");
                else
                    printf(" ");
        }
            printf("\n");
    }

    return 0;
}
