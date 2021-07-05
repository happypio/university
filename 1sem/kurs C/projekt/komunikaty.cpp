#include<gtk/gtk.h>
#include"main.hpp"
#include"obsluga.hpp"
#include"granie.hpp"
#include"ruchy.hpp"
int przegrana=0;
#include"komunikaty.hpp"
#include"algorytm.hpp"
#include<iostream>
int zmiana=0,spoko=1;
GtkWidget *okeja;
char *przegrany;
void okej2(){
    gtk_widget_set_sensitive (okno, true);
    gtk_window_close(GTK_WINDOW(okeja));
    }
void okejj(){
    gtk_widget_set_sensitive (okno, TRUE);
    czyszczenie_ekranu();
    gtk_window_close(GTK_WINDOW(okeja));
    uruchom_menu();
}
void przegraj(){
    gtk_widget_set_sensitive (okno, FALSE);
    GtkWidget *imionko,*etykieta,*przycisk1,*biel;
    imionko = gtk_label_new(NULL);
    if(spoko){
    if(plejer==0)
        przegrany=jeden;
    else
        przegrany=drugi;
    }

    okeja = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("PRZEGRANA",330,150,0,okeja);
    gtk_window_set_resizable(GTK_WINDOW(okeja),true);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(okeja),biel);
    etykieta = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "PRZEGRAŁ!");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,120,80);
    przycisk1=gtk_button_new_with_label("OK");
    nowy_przycisk(250,100,50,40,przycisk1,biel);
    g_signal_connect(G_OBJECT(przycisk1), "clicked",G_CALLBACK(okejj), NULL);
    gtk_label_set_markup(GTK_LABEL(imionko),przegrany);
    gtk_layout_put(GTK_LAYOUT(biel),imionko,80,20);
    g_signal_connect(G_OBJECT(okeja), "destroy", G_CALLBACK(sens), NULL);
    gtk_widget_show_all(okeja);
    przegrana=0;
    }
void zmien(){
    plejer=(plejer+1)%2;
    gtk_widget_destroy(kontr1);
    if(plejer==0)
        kontr1=gtk_image_new_from_file("kontroler.png");
    else
        kontr1=gtk_image_new_from_file("rkontroler.png");
    gtk_layout_put(GTK_LAYOUT(tlo),kontr1,-490,-130);
    if(single&&plejer==1)
        ruch_komp();
    gtk_widget_show_all(okno);
}
void sprawdz(){
    przegrana=1;
    for(int i=0;i<8;i++){
        if(kropki[pozy][pozx].tab[i]==0)
            przegrana=0;
        }
    if((pozx==0&&pozy==5)||(pozy==5&&pozx==14))
    {
        spoko=0;
        przegrana=1;
        if(pozx==0)
            przegrany=jeden;
        else
            przegrany=drugi;
    }
        if(przegrana)
            przegraj();
    zmiana=1;
    int licznik=0;
        for(int i=0;i<8;i++){
            if(kropki[pozy][pozx].tab[i]==1)
                licznik++;
            }
    if(licznik>1)
        zmiana=0;
        if(zmiana)
        zmien();

}
void zly_ruch(){
gtk_widget_set_sensitive (okno, FALSE);
    GtkWidget *etykieta,*przycisk1,*biel;
    okeja = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("ZŁY RUCH",300,100,0,okeja);
    gtk_window_set_resizable(GTK_WINDOW(okeja),true);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(okeja),biel);
    etykieta = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "WYKONAŁEŚ BŁĘDNY RUCH!");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,55,20);
    przycisk1=gtk_button_new_with_label("OK");
    nowy_przycisk(130,50,50,40,przycisk1,biel);
    g_signal_connect(G_OBJECT(przycisk1), "clicked",G_CALLBACK(okej2), NULL);
    g_signal_connect(G_OBJECT(okeja), "destroy", G_CALLBACK(sens), NULL);
    gtk_widget_show_all(okeja);

}
