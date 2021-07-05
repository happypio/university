#include<gtk/gtk.h>
#include"obsluga.hpp"
#include<iostream>
#include"main.hpp"
#include"granie.hpp"
#include"komunikaty.hpp"
#include"ruchy.hpp"
wierzcholek kropki[11][15];
int pozx=7,pozy=5;

void ustaw_kropki(){
    pozx=7;
    pozy=5;
    x=100,y=100;
    for(int i=0;i<11;i++){
        for(int j=0;j<15;j++){
            for(int z=0;z<8;z++)
                kropki[i][j].tab[z]=0;
        }
    }
    for(int i=0;i<8;i++){
        kropki[0][0].tab[i]=1;
        kropki[0][14].tab[i]=1;
        kropki[10][0].tab[i]=1;
        kropki[10][14].tab[i]=1;
    }
    kropki[0][0].tab[5]=0;
    kropki[0][14].tab[7]=0;
    kropki[10][0].tab[3]=0;
    kropki[10][14].tab[1]=0;
    for(int i=1;i<14;i++){
        for(int j=0;j<5;j++)
            kropki[0][i].tab[j]=1;
        for(int j=4;j<8;j++)
            kropki[10][i].tab[j]=1;
        kropki[10][i].tab[0]=1;
    }
    for(int i=1;i<10;i++){
        for(int j=6;j<11;j++)
            kropki[i][0].tab[j%8]=1;
        for(int j=2;j<7;j++)
            kropki[i][14].tab[j]=1;
    }
    kropki[4][0].tab[6]=0;
    kropki[6][0].tab[2]=0;
    kropki[4][14].tab[6]=0;
    kropki[6][14].tab[2]=0;
    kropki[5][0].tab[2]=0;
    kropki[5][0].tab[6]=0;
    kropki[5][14].tab[2]=0;
    kropki[5][14].tab[6]=0;
}
void zniszcz()
{
    gtk_widget_destroy(GTK_WIDGET(pilka));
}
void rysuj1(){
    if(kropki[pozy][pozx].tab[2]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("gora.png");
        else
            kreski[n]=gtk_image_new_from_file("rgora.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[2]=1;
        pozy--;
        kropki[pozy][pozx].tab[6]=1;
        y-=50;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj2(){
    if(kropki[pozy][pozx].tab[6]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("dol.png");
        else
            kreski[n]=gtk_image_new_from_file("rdol.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[6]=1;
        pozy++;
        kropki[pozy][pozx].tab[2]=1;
        y+=50;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj3(){
    if(kropki[pozy][pozx].tab[0]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("lewo.png");
        else
            kreski[n]=gtk_image_new_from_file("rlewo.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[0]=1;
        pozx--;
        kropki[pozy][pozx].tab[4]=1;
        x-=52;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj4(){
    if(kropki[pozy][pozx].tab[4]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("prawo.png");
        else
            kreski[n]=gtk_image_new_from_file("rprawo.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[4]=1;
        pozx++;
        kropki[pozy][pozx].tab[0]=1;
        x+=52;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj5(){
    if(kropki[pozy][pozx].tab[1]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("skosgl.png");
        else
            kreski[n]=gtk_image_new_from_file("rskosgl.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[1]=1;
        pozx--;
        pozy--;
        kropki[pozy][pozx].tab[5]=1;
        x-=52;
        y-=50;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj6(){
    if(kropki[pozy][pozx].tab[3]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("skosgp.png");
        else
            kreski[n]=gtk_image_new_from_file("rskosgp.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[3]=1;
        pozx++;
        pozy--;
        kropki[pozy][pozx].tab[7]=1;
        x+=52;
        y-=50;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj7(){
    if(kropki[pozy][pozx].tab[7]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("skosdl.png");
        else
            kreski[n]=gtk_image_new_from_file("rskosdl.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[7]=1;
        pozx--;
        pozy++;
        kropki[pozy][pozx].tab[3]=1;
        x-=52;
        y+=50;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
void rysuj8(){
    if(kropki[pozy][pozx].tab[5]==0){
        if(plejer==0)
            kreski[n]=gtk_image_new_from_file("skosdp.png");
        else
            kreski[n]=gtk_image_new_from_file("rskosdp.png");
        gtk_layout_put(GTK_LAYOUT(tlo),kreski[n],x,y);
        kropki[pozy][pozx].tab[5]=1;
        pozx++;
        pozy++;
        kropki[pozy][pozx].tab[1]=1;
        x+=52;
        y+=50;
        n++;
        zniszcz();
        pilka=gtk_image_new_from_file("pilka.png");
        gtk_layout_put(GTK_LAYOUT(tlo),pilka,x,y);
        gtk_widget_show_all(okno);
        sprawdz();
    }
    else
        zly_ruch();
}
