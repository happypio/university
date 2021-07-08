#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char slowo[100],nowa_nazwa[257];

typedef struct katalog {
char nazwa[257];
int licznik;
struct katalog* edges[257];
struct katalog* ojciec;
} katalog;
void wypisz (katalog* aktualny)
{
    if(strlen(aktualny->nazwa)==0)
        printf("/");
    else{
        wypisz(aktualny->ojciec);
        printf("%s/",aktualny->nazwa);
    }
    return;
}
int main (void)
{
    katalog *root = (katalog*)calloc(sizeof(katalog),1);
    katalog *aktualny=root;
    while(scanf("%s",slowo)!=EOF){
         if(slowo[0]=='m'){
            int czy_jest=0,z=0;
            scanf("%s",nowa_nazwa);
            while(z<aktualny->licznik&&!czy_jest){
                    if(strcmp(aktualny->edges[z]->nazwa,nowa_nazwa)==0){
                        czy_jest=1;
                    }
                    z++;
                }
            if(aktualny->licznik<256&&!czy_jest){
                aktualny->edges[aktualny->licznik]=(katalog*)calloc(sizeof(katalog),1);
                for(int unsigned j=0;j<strlen(nowa_nazwa);j++)
                    aktualny->edges[aktualny->licznik]->nazwa[j]=nowa_nazwa[j];
                aktualny->edges[aktualny->licznik]->ojciec=aktualny;
                aktualny->edges[aktualny->licznik]->licznik=0;
                aktualny->licznik++;
            }
         }
         else{
            if(slowo[0]=='c'){
                scanf("%s",nowa_nazwa);
                if(nowa_nazwa[0]=='.'&&nowa_nazwa[1]=='.'){
                    if(strlen(aktualny->nazwa)!=0)
                        aktualny=aktualny->ojciec;
                }
                else{
                int znaleziono=0,i=0;
                while(i<aktualny->licznik&&!znaleziono){
                    if(strcmp(aktualny->edges[i]->nazwa,nowa_nazwa)==0){
                        aktualny=aktualny->edges[i];
                        znaleziono=1;
                    }
                    i++;
                }
            }}
            else{
                if(slowo[0]=='p'){
                    wypisz(aktualny);
                    printf("\n");
                }
            }
         }
    }
    return 0;
}
