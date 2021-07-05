#include <gtk/gtk.h>
#include<iostream>
#include"main.hpp"
#include"granie.hpp"
GtkWidget *kreski[1000],*gora,*dol,*prawo,*lewo,*skosgl,*skosgp,*skosdl,*skosdp,*kontr1,*obraz,*pilka;
int n=0,plejer=0,single;
gint x=100,y=100;
char *jeden,*drugi;
#include"ruchy.hpp"
#include"obsluga.hpp"
#include"algorytm.hpp"
GtkWidget *wyjdz;
void przyciszek(GtkWidget *przycisk,gint sz,gint wy)
{
    nowy_przycisk(sz,wy,60,60,przycisk,tlo);
    gtk_widget_set_opacity(przycisk,0.01);
}

void kontroler(){
    przyciszek(gora,470,700);
    przyciszek(dol,470,820);
    przyciszek(prawo,530,760);
    przyciszek(lewo,410,760);
    przyciszek(skosgl,410,700);
    przyciszek(skosgp,530,700);
    przyciszek(skosdl,410,820);
    przyciszek(skosdp,530,820);
}
void wyswietl_plansze(const gchar *imionko)
{
    GtkWidget *boisko,*papier,*zawodnik,*zawodnik2;
    gtk_window_close(GTK_WINDOW(wybor));
    gtk_container_set_border_width (GTK_CONTAINER(okno),0);
    czyszczenie_ekranu();
    papier = gtk_label_new(NULL);
    zawodnik = gtk_label_new(NULL);
    zawodnik2=gtk_label_new(NULL);
    const gchar *imie1= "<b><i><span font = '30'><span fgcolor='#30e0ff'>\%s</span></span></i></b>";
    const gchar *imie2= "<b><i><span font = '30'><span fgcolor='#ff305d'>\%s</span></span></i></b>";
    char *markup1=g_markup_printf_escaped(imie1,gracz1);
    char *markup2=g_markup_printf_escaped(imie2,imionko);
    jeden=markup1;
    drugi=markup2;
    gtk_label_set_markup(GTK_LABEL(papier), "<b><i><span fgcolor='#eeeeee'><span font = '40'>PAPER SOCCER</span></span></i></b>");
    gtk_label_set_markup(GTK_LABEL(zawodnik),markup1);
    gtk_label_set_markup(GTK_LABEL(zawodnik2),markup2);
    tlo = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(okno),tlo);
    boisko=gtk_image_new_from_file("boisko_git.png");
    if(plejer)
        kontr1=gtk_image_new_from_file("rkontroler.png");
    else
        kontr1=gtk_image_new_from_file("kontroler.png");
    pilka=gtk_image_new_from_file("pilka.png");
    gtk_layout_put(GTK_LAYOUT(tlo),boisko,100,100);
    gtk_layout_put(GTK_LAYOUT(tlo),papier,320,25);
    gtk_layout_put(GTK_LAYOUT(tlo),pilka,100,100);
    gtk_layout_put(GTK_LAYOUT(tlo),zawodnik,60,710);
    gtk_layout_put(GTK_LAYOUT(tlo),zawodnik2,700,710);
    kontroler();
    gtk_layout_put(GTK_LAYOUT(tlo),kontr1,-490,-130);
    wyjdz=gtk_button_new_with_label("WRÓĆ DO MENU");
    nowy_przycisk(800,800,150,60,wyjdz,tlo);
    gtk_widget_show_all(okno);
}
void oki()
{
    gtk_widget_set_sensitive (okno, true);
    gtk_window_close(GTK_WINDOW(obraz));
}
void zaczyna(char *osoba){
    GtkWidget *imionko,*etykieta,*przycisk1,*biel;
    imionko = gtk_label_new(NULL);
    obraz = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("GRAMY!",330,150,0,obraz);
    gtk_window_set_resizable(GTK_WINDOW(obraz),true);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(obraz),biel);
    etykieta = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "  ZACZYNA!");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,120,80);
    przycisk1=gtk_button_new_with_label("OK");
    nowy_przycisk(250,100,50,40,przycisk1,biel);
    g_signal_connect(G_OBJECT(przycisk1), "clicked",G_CALLBACK(oki), NULL);
    gtk_label_set_markup(GTK_LABEL(imionko),osoba);
    gtk_layout_put(GTK_LAYOUT(biel),imionko,80,20);
    g_signal_connect(G_OBJECT(obraz), "destroy", G_CALLBACK(sens), NULL);
    gtk_widget_show_all(obraz);
}
int losuj(){
    srand( time( NULL ) );
    return rand()%2;
}
void graj_multi()
{
    single=0;
    plejer=losuj();
    gora=gtk_button_new();
    dol=gtk_button_new();
    lewo=gtk_button_new();
    prawo=gtk_button_new();
    skosdl=gtk_button_new();
    skosdp=gtk_button_new();
    skosgl=gtk_button_new();
    skosgp=gtk_button_new();
    wyswietl_plansze(gracz2);
    ustaw_kropki();
    gtk_window_set_title (GTK_WINDOW(okno), "MULTIPLAYER");
    if(plejer)
        zaczyna(drugi);
    else
        zaczyna(jeden);
    g_signal_connect(G_OBJECT(wyjdz), "clicked", G_CALLBACK(wroc), NULL);
    g_signal_connect(G_OBJECT(dol), "clicked", G_CALLBACK(rysuj2), NULL);
    g_signal_connect(G_OBJECT(gora), "clicked", G_CALLBACK(rysuj1), NULL);
    g_signal_connect(G_OBJECT(lewo), "clicked", G_CALLBACK(rysuj3), NULL);
    g_signal_connect(G_OBJECT(prawo), "clicked", G_CALLBACK(rysuj4), NULL);
    g_signal_connect(G_OBJECT(skosdl), "clicked", G_CALLBACK(rysuj7), NULL);
    g_signal_connect(G_OBJECT(skosdp), "clicked", G_CALLBACK(rysuj8), NULL);
    g_signal_connect(G_OBJECT(skosgl), "clicked", G_CALLBACK(rysuj5), NULL);
    g_signal_connect(G_OBJECT(skosgp), "clicked", G_CALLBACK(rysuj6), NULL);
    gtk_widget_show_all(okno);
}

void graj_single()
{
    single=1;
    plejer=losuj();
    gora=gtk_button_new();
    dol=gtk_button_new();
    lewo=gtk_button_new();
    prawo=gtk_button_new();
    skosdl=gtk_button_new();
    skosdp=gtk_button_new();
    skosgl=gtk_button_new();
    skosgp=gtk_button_new();
    wyswietl_plansze("KOMPUTER");
    ustaw_kropki();
    gtk_window_set_title (GTK_WINDOW(okno), "SINGLEPLAYER");
    if(plejer)
        zaczyna(drugi);
    else
        zaczyna(jeden);
    if(plejer)
        ruch_komp();
    g_signal_connect(G_OBJECT(wyjdz), "clicked", G_CALLBACK(wroc), NULL);
    g_signal_connect(G_OBJECT(dol), "clicked", G_CALLBACK(rysuj2), NULL);
    g_signal_connect(G_OBJECT(gora), "clicked", G_CALLBACK(rysuj1), NULL);
    g_signal_connect(G_OBJECT(lewo), "clicked", G_CALLBACK(rysuj3), NULL);
    g_signal_connect(G_OBJECT(prawo), "clicked", G_CALLBACK(rysuj4), NULL);
    g_signal_connect(G_OBJECT(skosdl), "clicked", G_CALLBACK(rysuj7), NULL);
    g_signal_connect(G_OBJECT(skosdp), "clicked", G_CALLBACK(rysuj8), NULL);
    g_signal_connect(G_OBJECT(skosgl), "clicked", G_CALLBACK(rysuj5), NULL);
    g_signal_connect(G_OBJECT(skosgp), "clicked", G_CALLBACK(rysuj6), NULL);
}
