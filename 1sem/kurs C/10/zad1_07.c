#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    int koniec_kluczu=0,caly_klucz=0;
    char litera[1],szyfr[1];
    FILE *klucz=fopen(argv[0],"r");
    FILE *plik=fopen(argv[1],"r");
    fread(szyfr,1,1,klucz);
    while(fread(litera,1,1,plik)==1){
        if(koniec_kluczu){
            fseek(klucz,0,SEEK_SET);
            fread(szyfr,1,1,klucz);
            caly_klucz=1;
        }
        litera[0]=szyfr[0]^litera[0];
        fwrite(litera,1,1,plik);
        if(fread(szyfr,1,1,klucz)!=1)
            koniec_kluczu=1;
    }
    if(caly_klucz==0){
        int koniec_pliku=0;
      fseek(plik,0,SEEK_SET);
      fread(litera,1,1,plik);
      while(fread(szyfr,1,1,klucz)==1){
            if(koniec_pliku){
                fseek(plik,0,SEEK_SET);
                fread(litera,1,1,plik);
            }
            litera[0]=szyfr[0]^litera[0];
            fwrite(litera,1,1,plik);
            if(fread(litera,1,1,plik)!=1)
                koniec_pliku=1;
      }
    }
    fclose(klucz);
    fclose(plik);
    return 0;
}
