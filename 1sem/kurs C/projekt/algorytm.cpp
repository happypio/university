#include<iostream>
#include<gtk/gtk.h>
#include<iostream>
#include"ruchy.hpp"
#include"komunikaty.hpp"
#include"algorytm.hpp"
#include"algorytmodp.hpp"
int ruchy[50],najruchy[50],najx=10,najy=9,najlicznik=0,wygrac=0,zapisane=0,minodpx=30,minodpy=30;
int rusz(int gdzie, int co){
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
void zapisz(int licznik){
    for(int i=0;i<licznik;i++)
        najruchy[i]=ruchy[i];
    najx=pozx;
    najy=pozy;
    najlicznik=licznik;
}
void powrot(int licznik){

    kropki[pozy][pozx].tab[(ruchy[licznik-1]+4)%8]=0;
    pozy=rusz((ruchy[licznik-1]+4)%8,1);
    pozx=rusz((ruchy[licznik-1]+4)%8,0);
    kropki[pozy][pozx].tab[ruchy[licznik-1]]=0;
   //std::cout<<"pozycja to "<<pozy<<" "<<pozx<<" "<<ruchy[licznik-1]<<"\n";
}
int przegranie()
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
int wygrana()
{
    if(pozx==0&&pozy==5)
        return 1;
    else
        return 0;
}
int odbicie(){
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
int bezw(int x)
{
    if(x>0) return x;
    return -x;
}
void rekurencja(int tab[], int licznik)
{
    if(licznik>45)
        return;
    /*if(licznik==3){
        return;
        powrot(licznik);
    }*/
    if(wygrac){
        powrot(licznik);
        return;
    }
    if(licznik==0){
    if(wygrana()){
            //std::cout<<"wygrana licznik: "<<licznik<<" \n";
            zapisz(licznik);
            powrot(licznik);
            wygrac=1;
            return;
            }
    for(int i=0;i<8;i++){
            if(kropki[pozy][pozx].tab[i]==0){
                if(wygrac){
                    powrot(licznik);
                    return;
                }
                kropki[pozy][pozx].tab[i]=1;
                pozy=rusz(i,1);
                pozx=rusz(i,0);
                kropki[pozy][pozx].tab[(i+4)%8]=1;
                tab[licznik]=i;
                //std::cout<<" "<<ruchy[licznik]<<"\n";
                rekurencja(tab,licznik+1);
            }
        }
        //std::cout<<"cos";
    }
    if(odbicie()&&!przegranie()){
        if(wygrana()){
            //std::cout<<"wygrana licznik: "<<licznik<<" \n";
            zapisz(licznik);
            powrot(licznik);
            //for(int i=0;i<najlicznik;i++)
                //std::cout<<najruchy[i]<<" ";
                //std::cout<<najlicznik<<"\n";
            wygrac=1;
            return;
            }
        for(int i=0;i<8;i++){
            if(kropki[pozy][pozx].tab[i]==0){
                if(wygrac){
                    powrot(licznik);
                    return;
                }
                kropki[pozy][pozx].tab[i]=1;
                pozy=rusz(i,1);
                pozx=rusz(i,0);
                kropki[pozy][pozx].tab[(i+4)%8]=1;
                tab[licznik]=i;
                //std::cout<<i<<" "<<tab[licznik]<<" kuku "<<"\n";
                rekurencja(tab,licznik+1);
            }
        }
        //std::cout<<"COSIEK";
    }
    else{
        if(licznik>0){
        if(!przegranie()){
            odpowiedz();
            if(odpx<minodpx){
                    minodpx=odpx,minodpy=odpy;
                    zapisz(licznik);
                    zapisane=1;
                }
                else{
                    if(bezw(odpy-5)<bezw(minodpy-5)&&odpx<=minodpx){
                        minodpy=odpy,minodpx=odpx;
                        zapisz(licznik);
                        zapisane=1;
                    }
                    if(!zapisane)
                    zapisz(licznik);
                }
            //std::cout<<"hej pier pozycja: "<<pozy<<" "<<pozx<<"\n";
            /*if(pozx<najx){
                if(odpx<minodpx){
                    minodpx=odpx,minodpy=odpy;
                    zapisz(licznik);
                    zapisane=1;
                }
                else{
                    if(bezw(odpy-5)<bezw(minodpy-5)&&odpx<=minodpx){
                        minodpy=odpy,minodpx=odpx;
                        zapisz(licznik);
                        zapisane=1;
                    }
                }

                //std::cout<<pozx<<" kaka "<<licznik<<"\n";
            }
            else{
                if(bezw(pozy-5)<bezw(najy-5)&&pozx<=najx){
                    if(odpx<minodpx){
                    minodpy=odpy,minodpx=odpx;
                    zapisz(licznik);
                    zapisane=1;
                }
                else{
                    if(bezw(odpy-5)<bezw(minodpy-5)&&odpx<=minodpx){
                        minodpy=odpy,minodpx=odpx;
                        zapisz(licznik);
                        zapisane=1;
                    }
                }
                    //std::cout<<pozx<<" kiki "<<licznik<<"\n";
                }
                else{
                    if(najlicznik<licznik&&pozx<=najx&&bezw(pozy-5)<=bezw(najy-5)){
                    if(odpx<minodpx){
                    minodpy=odpy,minodpx=odpx;
                    zapisz(licznik);
                    zapisane=1;
                }
                else{
                    if(bezw(odpy-5)<bezw(minodpy-5)&&odpx<=minodpx){
                    minodpy=odpy,minodpx=odpx;
                        zapisz(licznik);
                        zapisane=1;
                    }
                }
                    //std::cout<<pozx<<" kuku "<<licznik<<"\n";
                }
                if(!zapisane){
                if(odpx<minodpx){
                minodpy=odpy,minodpx=odpx;
                    zapisz(licznik);
                    zapisane=1;
                }
                else{
                    if(bezw(odpy-5)<bezw(minodpy-5)&&odpx<=minodpx){
                    minodpy=odpy,minodpx=odpx;
                        zapisz(licznik);
                        zapisane=1;
                    }
                }
                if(!zapisane)
                    zapisz(licznik);
                }
                }
            }*/

        }
    }
    }
    if(licznik!=0)
        powrot(licznik);
    return;
}

void ruch_komp()
{
    ruchy[40]={0},najruchy[40]={0},najx=pozx,najy=pozy,najlicznik=0,wygrac=0,zapisane=0,minodpx=30,minodpy=30;
    int poczx=pozx,poczy=pozy;
    rekurencja(ruchy,0);
    pozx=poczx;
    pozy=poczy;
    //std::cout<<najruchy[0]<<" "<<"aktualne: "<<pozy<<" "<<pozx<<" i zmienione "<<najy<<" "<<najx<<"\n";
    //pozx=najx;
    //pozy=najy;
    for(int i=0;i<najlicznik;i++){
        if(!przegrana){
            switch(najruchy[i]){
            case 0:
                rysuj3();
            break;
            case 1:
                rysuj5();
            break;
            case 2:
                rysuj1();
            break;
            case 3:
                rysuj6();
            break;
            case 4:
                rysuj4();
            break;
            case 5:
                rysuj8();
            break;
            case 6:
                rysuj2();
            break;
            case 7:
                rysuj7();
            break;
            }
        }
    }
    }
