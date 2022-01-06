#include<stdio.h>
#include<string.h>
int main(void)
{
    int czekaj=0,i=0,j=0,naw_otw=0,element[10005]={0},szukam=0,rob=0;
    char c,identyfik[10005],zmienna[10005];
    while((c=getchar())!=EOF)
    {
        if((rob||(!czekaj&&naw_otw&&element[naw_otw]))&&!szukam&&c!=' '&&c!=')'&&c!='\n'){
            printf(", ");
            rob=0;
           }
        if(czekaj){
            if(c!=' '&&c!='\n'&&c!=')'&&c!='0'&&c!='1'&&c!='2'&&c!='3'&&c!='4'&&c!='5'&&c!='6'&&c!='7'&&c!='8'&&c!='9'){
                identyfik[i]=c;
                i++;
                //printf("%c\n",c);
            }
            else{
                if(i>0){
                    printf("%.*s(",i,identyfik);
                    i=0,czekaj=0;
                }
            }
        }
        if(c=='('){
            czekaj=1;
            naw_otw++;
        }
        if(!czekaj&&c!=' '&&c!='('&&c!=')'&&c!='\n'){
            szukam++;
            zmienna[j]=c;
            j++;
            //printf("to jest j %d",j);
        }
        else{
            if(j>0/*&&!czekaj*/){
                printf("%.*s",j,zmienna);
                int f=0;
                if(c=='(')
                    f=1;
                j=0,element[naw_otw-f]++,szukam=0,rob=1;
            }
        }
        if(c==')'){
            element[naw_otw]=0,rob=0;
            naw_otw--;
            if(naw_otw>0)
                element[naw_otw]++;
            printf(")");
        }

    }
    return 0;
}
