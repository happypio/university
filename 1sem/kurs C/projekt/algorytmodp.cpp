#include<iostream>
#include<gtk/gtk.h>
#include<iostream>
#include"ruchy.hpp"
#include"komunikaty.hpp"
int odpx=10,odpy=9;
#include"algorytmodp.hpp"
int ruchy2[50],najruchy2[50],najlicznik2=0,wygrac2=0,zapisane2=0;
int rusz2(int gdzie, int co){
    switch(gdzie){
        case 0:
            if(co)
            return pozy;
            else
            return pozx-1;
        break;
        case 1:
        if(co)
            return pozy-1;
            else
            return pozx-1;
        break;
        case 2:
        if(co)
            return pozy-1;
            else
            return pozx;
        break;
        case 3:
        if(co)
            return pozy-1;
            else
            return pozx+1;
        break;
        case 4:
        if(co)
            return pozy;
            else
            return pozx+1;
        break;
        case 5:
        if(co)
            return pozy+1;
            else
            return pozx+1;
        break;
        case 6:
        if(co)
            return pozy+1;
            else
            return pozx;
        break;
        case 7:
        if(co)
            return pozy+1;
            else
            return pozx-1;
        break;
    }
}
void zapisz2(int licznik){
    for(int i=0;i<licznik;i++)
        najruchy2[i]=ruchy2[i];
    odpx=pozx;
    odpy=pozy;
    najlicznik2=licznik;
}
void powrot2(int licznik){

    kropki[pozy][pozx].tab[(ruchy2[licznik-1]+4)%8]=0;
    pozy=rusz2((ruchy2[licznik-1]+4)%8,1);
    pozx=rusz2((ruchy2[licznik-1]+4)%8,0);
    kropki[pozy][pozx].tab[ruchy2[licznik-1]]=0;
   //std::cout<<"pozycja to "<<pozy<<" "<<pozx<<" "<<ruchy[licznik-1]<<"\n";
}
int przegranie2()
{
    int przegr=1;
    for(int i=0;i<8;i++){
        if(kropki[pozy][pozx].tab[i]==0)
            przegr=0;
        }
     if(pozy==5&&pozx==14)
    {
        przegr=1;
    }
    return przegr;

}
int wygrana2()
{
    if(pozx==14&&pozy==5)
        return 1;
    else
        return 0;
}
int odbicie2(){
    int licznik=0;
        for(int i=0;i<8;i++){
            if(kropki[pozy][pozx].tab[i]==1)
                licznik++;
            }
    //if(pozx==7&&pozy==5);
        //return 1;
    if(licznik>1)
        return 1;
    else return 0;
}
int bezw2(int x)
{
    if(x>0) return x;
    return -x;
}
void rekurencja2(int tab[], int licznik)
{
    if(licznik>20)
        return;
    /*if(licznik==3){
        return;
        powrot(licznik);
    }*/
    if(wygrac2){
        powrot2(licznik);
        return;
    }
    if(licznik==0){
    if(wygrana2()){
            //std::cout<<"wygrana licznik: "<<licznik<<" \n";
            zapisz2(licznik);
            powrot2(licznik);
            wygrac2=1;
            return;
            }
    for(int i=0;i<8;i++){
            if(kropki[pozy][pozx].tab[i]==0){
                if(wygrac2){
                    powrot2(licznik);
                    return;
                }
                kropki[pozy][pozx].tab[i]=1;
                pozy=rusz2(i,1);
                pozx=rusz2(i,0);
                kropki[pozy][pozx].tab[(i+4)%8]=1;
                tab[licznik]=i;
                //std::cout<<" "<<ruchy[licznik]<<"\n";
                rekurencja2(tab,licznik+1);
            }
        }
        //std::cout<<"cos";
    }
    if(odbicie2()){
        if(wygrana2()){
            //std::cout<<"wygrana licznik: "<<licznik<<" \n";
            zapisz2(licznik);
            powrot2(licznik);
            //for(int i=0;i<najlicznik;i++)
                //std::cout<<najruchy[i]<<" ";
                //std::cout<<najlicznik<<"\n";
            wygrac2=1;
            return;
            }
        for(int i=0;i<8;i++){
            if(kropki[pozy][pozx].tab[i]==0){
                if(wygrac2){
                    powrot2(licznik);
                    return;
                }
                kropki[pozy][pozx].tab[i]=1;
                pozy=rusz2(i,1);
                pozx=rusz2(i,0);
                kropki[pozy][pozx].tab[(i+4)%8]=1;
                tab[licznik]=i;
                //std::cout<<i<<" "<<tab[licznik]<<" kuku "<<"\n";
                rekurencja2(tab,licznik+1);
            }
        }
        //std::cout<<"COSIEK";
    }
    else{
        if(licznik>0){
        if(!przegranie2()){
            //std::cout<<"hej pier pozycja: "<<pozy<<" "<<pozx<<"\n";
            if(pozx>odpx){

                zapisz2(licznik);
                zapisane2=1;
                //std::cout<<pozx<<" kaka "<<licznik<<"\n";
            }
            else{
                if(bezw2(pozy-5)<bezw2(odpy-5)&&pozx>=odpx){
                    zapisz2(licznik);
                    zapisane2=1;
                    //std::cout<<pozx<<" kiki "<<licznik<<"\n";
                }
                else{
                    if(najlicznik2<licznik&&pozx>=odpx&&bezw2(pozy-5)<=bezw2(odpy-5)){
                    zapisz2(licznik);
                    zapisane2=1;
                    //std::cout<<pozx<<" kuku "<<licznik<<"\n";
                }
                if(!zapisane2)
                    zapisz2(licznik);
                }
            }

        }
    }
    }
    if(licznik!=0)
        powrot2(licznik);
    return;
}
void odpowiedz()
{
    odpy=pozy;odpx=pozx,ruchy2[40]={0},najruchy2[40]={0},najlicznik2=0,wygrac2=0,zapisane2=0;
    int poczx=pozx,poczy=pozy;
    rekurencja2(ruchy2,0);
    pozx=poczx,pozy=poczy;
}
