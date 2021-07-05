#include <gtk/gtk.h>
#include<iostream>
const gchar *gracz1,*gracz2;
#include"main.hpp"
#include"obsluga.hpp"

void uruchom_menu()
{

    GtkWidget *boisko;
    GtkWidget *singleplayer;
    GtkWidget *multiplayer;
    GtkWidget *wyjdz;
    gtk_container_set_border_width (GTK_CONTAINER(okno),100);
    gtk_window_set_title (GTK_WINDOW(okno), "MENU");
    tlo = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(okno),tlo);
    boisko=gtk_image_new_from_file("messi.jpg");
    gtk_layout_put(GTK_LAYOUT(tlo),boisko,0,0);

    singleplayer=gtk_button_new_with_label("SINGLEPLAYER");
    nowy_przycisk(300,200,200,70,singleplayer,tlo);
    multiplayer=gtk_button_new_with_label("MULTIPLAYER");
    nowy_przycisk(300 , 300 ,200 ,70, multiplayer,tlo);
    wyjdz=gtk_button_new_with_label("WYJDŹ");
    nowy_przycisk(300,550,200,70,wyjdz,tlo);

    //gtk_button_clicked(GTK_BUTTON(singleplayer));
    g_signal_connect(G_OBJECT(singleplayer), "clicked", G_CALLBACK(wybor_graczy2), NULL);
    g_signal_connect(G_OBJECT(multiplayer), "clicked", G_CALLBACK(wybor_graczy), NULL);
    g_signal_connect(G_OBJECT(wyjdz), "clicked", G_CALLBACK(wychodzenie), NULL);
    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(okno);
}
