#include <gtk/gtk.h>
#include<iostream>
GtkWidget *okno,*tlo;
GdkRGBA podswietlony,zielony;
#include"main.hpp"
#include"obsluga.hpp"
int main( int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    zielony.red = 0; zielony.green = 1; zielony.blue = 0; zielony.alpha = 0.43;
    podswietlony.red = 0.9; podswietlony.green = 0.45; podswietlony.blue = 0.2; podswietlony.alpha = 0.90;
    okno = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("MENU",1000,900,100,okno);
    gtk_widget_override_background_color(okno,GTK_STATE_FLAG_NORMAL, &zielony);
    uruchom_menu();
    gtk_main();

    return 0;
}
