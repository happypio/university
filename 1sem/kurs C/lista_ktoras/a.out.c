#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    int caly_klucz=0,petla_klucza=0;
    char litera[1],szyfr[1];
    FILE *klucz=fopen(argv[0],"rb");
    FILE *plik=fopen(argv[1],"rb+");
    fread(szyfr,sizeof(szyfr),1,klucz);
    while(fread(litera,sizeof(litera),1,plik)==1&&petla_klucza!=2){
        fseek(plik,-1,SEEK_CUR);
        litera[0]=szyfr[0]^litera[0];
        fwrite(litera,sizeof(litera),1,plik);
        if(fread(szyfr,sizeof(szyfr),1,klucz)!=1){
            fseek(klucz,0,SEEK_SET);
            fread(szyfr,sizeof(szyfr),1,klucz);
            caly_klucz=1;
            if(petla_klucza==1)
                petla_klucza=2;
        }
        if(fread(litera,sizeof(litera),1,plik)!=1){
            if(caly_klucz==0){
                fseek(plik,0,SEEK_SET);
            if(petla_klucza!=2)
                petla_klucza=1;
                }
           else{
                fseek(plik,0,SEEK_END);
            }
        }
        else{
            fseek(plik,-1,SEEK_CUR);
        }
    }
    /*if(caly_klucz==0){
        int koniec_pliku=0;
      fseek(plik,0,SEEK_SET);
      fread(litera,sizeof(litera),1,plik);
      while(fread(szyfr,sizeof(szyfr),1,klucz)==1){
            if(koniec_pliku){
                fseek(plik,0,SEEK_SET);
                fread(litera,sizeof(litera),1,plik);
            }
            fseek(plik,-1,SEEK_CUR);
            litera[0]=szyfr[0]^litera[0];
            fwrite(litera,sizeof(litera),1,plik);
            if(fread(litera,sizeof(litera),1,plik)!=1)
                koniec_pliku=1;
      }
    }*/
    fclose(klucz);
    fclose(plik);
    return 0;
}
