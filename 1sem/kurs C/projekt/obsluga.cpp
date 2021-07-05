#include <gtk/gtk.h>
#include<iostream>
#include"main.hpp"
#include "obsluga.hpp"
#include "granie.hpp"

GtkWidget *wyjscie,*wybor,*ostrzezenie,*player2;
void zamknij() {
    gtk_widget_set_sensitive (okno, TRUE);
  gtk_window_close(GTK_WINDOW(wyjscie));
}
void sens()
{
    gtk_widget_set_sensitive (okno, TRUE);
}
void sens1(GtkWidget *zamkniecie)
{
    gtk_widget_set_sensitive (wybor, TRUE);
}
void czyszczenie_ekranu() {

    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(okno));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}

void nowy_przycisk(gint x, gint y,gint sz, gint wy, GtkWidget *przycisk,GtkWidget *gdzie){
    gtk_widget_set_opacity(przycisk,0.8);
    gtk_layout_put(GTK_LAYOUT(gdzie),przycisk,x,y);
    gtk_widget_set_size_request(przycisk, sz, wy);
    gtk_widget_override_background_color(przycisk,GTK_STATE_FLAG_PRELIGHT, &podswietlony);
}

void ustaw_okno(const gchar *title, gint x, gint y, gint kont,GtkWidget *okienko){
    gtk_window_set_position (GTK_WINDOW(okienko), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size (GTK_WINDOW(okienko), x, y);
    gtk_window_set_resizable(GTK_WINDOW(okienko),0);
    gtk_window_set_title (GTK_WINDOW(okienko), title);
    gtk_container_set_border_width (GTK_CONTAINER(okienko),kont);
}

void wychodzenie(){
    gtk_widget_set_sensitive (okno, FALSE);
    GtkWidget *etykieta,*przycisk1,*biel,*przycisk2;
    wyjscie = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("WYJŚCIE",200,90,0,wyjscie);
    gtk_window_set_resizable(GTK_WINDOW(wyjscie),true);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(wyjscie),biel);
    etykieta = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "Czy na pewno chcesz wyjść?");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,11,10);
    przycisk1=gtk_button_new_with_label("TAK");
    nowy_przycisk(40,40,50,40,przycisk1,biel);
    przycisk2=gtk_button_new_with_label("NIE");
    nowy_przycisk(110,40,50,40,przycisk2,biel);
    g_signal_connect(G_OBJECT(przycisk1), "clicked",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(przycisk2), "clicked", G_CALLBACK(zamknij), NULL);
    g_signal_connect(G_OBJECT(wyjscie), "destroy", G_CALLBACK(sens), NULL);
    gtk_widget_show_all(wyjscie);
}

void powroc(){
gtk_widget_set_sensitive (okno, TRUE);
    czyszczenie_ekranu();
    zamknij();
    uruchom_menu();
}
void wroc(){
    gtk_widget_set_sensitive (okno, FALSE);
    GtkWidget *etykieta,*przycisk1,*biel,*przycisk2,*etykieta2;
    wyjscie = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("POWRÓT DO MENU",330,150,0,wyjscie);
    gtk_window_set_resizable(GTK_WINDOW(wyjscie),true);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(wyjscie),biel);
    etykieta = gtk_label_new(NULL);
    etykieta2=gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "Czy na pewno chcesz wrócić?");
    gtk_label_set_markup(GTK_LABEL(etykieta2), "- gra zostanie przerwana, a postępy utracone.");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,60,10);
    gtk_layout_put(GTK_LAYOUT(biel),etykieta2,11,40);
    przycisk1=gtk_button_new_with_label("TAK");
    nowy_przycisk(100,80,50,40,przycisk1,biel);
    przycisk2=gtk_button_new_with_label("NIE");
    nowy_przycisk(170,80,50,40,przycisk2,biel);
    g_signal_connect(G_OBJECT(przycisk1), "clicked",G_CALLBACK(powroc), NULL);
    g_signal_connect(G_OBJECT(przycisk2), "clicked", G_CALLBACK(zamknij), NULL);
    g_signal_connect(G_OBJECT(wyjscie), "destroy", G_CALLBACK(sens), NULL);
    gtk_widget_show_all(wyjscie);
}
void zamykaj() {
gtk_widget_set_sensitive (okno, TRUE);
gtk_widget_set_sensitive (wybor, TRUE);
  gtk_window_close(GTK_WINDOW(ostrzezenie));
    }
void multigracze(){
gtk_widget_set_sensitive (okno, FALSE);
gtk_widget_set_sensitive (wybor, false);
        GtkWidget *zamknij1,*etykieta,*etykieta2,*biel;
        ostrzezenie=gtk_window_new (GTK_WINDOW_TOPLEVEL);
        ustaw_okno("UWAGA",300,100,0,ostrzezenie);
        gtk_window_set_resizable(GTK_WINDOW(ostrzezenie),true);
        biel = gtk_layout_new(NULL,NULL);
        gtk_container_add(GTK_CONTAINER(ostrzezenie),biel);
        etykieta = gtk_label_new(NULL);
        etykieta2 = gtk_label_new(NULL);
        zamknij1=gtk_button_new_with_label("OK");
        nowy_przycisk(120,50,60,30,zamknij1,biel);
        gtk_label_set_markup(GTK_LABEL(etykieta), "Nazwy graczów musi się składać");
        gtk_label_set_markup(GTK_LABEL(etykieta2), "z co najmniej jednego znaku!");
        gtk_layout_put(GTK_LAYOUT(biel),etykieta,45,5);
        gtk_layout_put(GTK_LAYOUT(biel),etykieta2,50,20);
        gtk_widget_show_all(ostrzezenie);
        g_signal_connect(G_OBJECT(ostrzezenie), "destroy", G_CALLBACK(sens1), NULL);
        g_signal_connect(G_OBJECT(zamknij1), "clicked", G_CALLBACK(zamykaj), NULL);
}
static void enter_callback( GtkWidget *widget,GtkWidget *entry )
{
  gracz1 = gtk_entry_get_text (GTK_ENTRY (entry));
  gracz2 = gtk_entry_get_text (GTK_ENTRY (player2));
  if(strlen(gracz1)==0||strlen(gracz2)==0)
        multigracze();
    else
    gtk_widget_set_sensitive (okno, true);
    graj_multi();

}
void wybor_graczy(){
    gtk_widget_set_sensitive (okno, false);
    GtkWidget *etykieta,*etykieta1,*etykieta2,*biel,*player1,*okej,*murawa;
    wybor = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("GRACZE",700,478,0,wybor);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(wybor),biel);
    murawa=gtk_image_new_from_file("murawa.jpg");
    gtk_layout_put(GTK_LAYOUT(biel),murawa,0,0);
    etykieta = gtk_label_new(NULL);
    etykieta1 = gtk_label_new(NULL);
    etykieta2 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "<b><span fgcolor='#140000'><span font = '30'>Podaj nazwy graczów:</span></span></b>");
    gtk_label_set_markup(GTK_LABEL(etykieta1), "<span font = '30'><span fgcolor='#140000'>GRACZ 1 </span></span>");
    gtk_label_set_markup(GTK_LABEL(etykieta2), "<span font = '30'><span fgcolor='#140000'>GRACZ 2 </span></span>");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,160,30);
    gtk_layout_put(GTK_LAYOUT(biel),etykieta1,30,150);
    gtk_layout_put(GTK_LAYOUT(biel),etykieta2,30,300);
    player1 = gtk_entry_new();
    player2 = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (player1), 10);
    gtk_entry_set_max_length (GTK_ENTRY (player2), 10);
    gtk_entry_set_text (GTK_ENTRY (player1), "PLAYER_1");
    gtk_entry_set_text (GTK_ENTRY (player2), "PLAYER_2");
    gtk_layout_put(GTK_LAYOUT(biel),player1,300,160);
    gtk_layout_put(GTK_LAYOUT(biel),player2,300,310);
    okej=gtk_button_new_with_label("GOTOWE!");
    nowy_przycisk(550,410,80,40,okej,biel);
    g_signal_connect(G_OBJECT(wybor), "destroy", G_CALLBACK(sens), NULL);
    g_signal_connect(G_OBJECT(okej), "clicked", G_CALLBACK(enter_callback), player1);
    gtk_widget_show_all(wybor);

}
static void enter_callback2( GtkWidget *widget,GtkWidget *entry )
{
  gracz1 = gtk_entry_get_text (GTK_ENTRY (entry));
  if(strlen(gracz1)==0)
        multigracze();
    else
    gtk_widget_set_sensitive (okno, true);
    graj_single();

}
void wybor_graczy2(){
    gtk_widget_set_sensitive (okno, false);
    GtkWidget *etykieta,*etykieta1,*etykieta2,*biel,*player1,*okej,*murawa;
    wybor = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    ustaw_okno("GRACZE",700,478,0,wybor);
    biel = gtk_layout_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(wybor),biel);
    murawa=gtk_image_new_from_file("murawa.jpg");
    gtk_layout_put(GTK_LAYOUT(biel),murawa,0,0);
    etykieta = gtk_label_new(NULL);
    etykieta1 = gtk_label_new(NULL);
    etykieta2 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(etykieta), "<b><span fgcolor='#140000'><span font = '30'>Podaj swoją nazwę:</span></span></b>");
    gtk_label_set_markup(GTK_LABEL(etykieta1), "<span font = '30'><span fgcolor='#140000'>GRACZ 1 </span></span>");
    gtk_label_set_markup(GTK_LABEL(etykieta2), "<span font = '30'><span fgcolor='#140000'>KOMPUTER </span></span>");
    gtk_layout_put(GTK_LAYOUT(biel),etykieta,160,30);
    gtk_layout_put(GTK_LAYOUT(biel),etykieta1,30,150);
    gtk_layout_put(GTK_LAYOUT(biel),etykieta2,30,300);
    player1 = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (player1), 20);
    gtk_entry_set_text (GTK_ENTRY (player1), "PLAYER_1");
    gtk_layout_put(GTK_LAYOUT(biel),player1,300,160);
    okej=gtk_button_new_with_label("GOTOWE!");
    nowy_przycisk(550,410,80,40,okej,biel);
    g_signal_connect(G_OBJECT(wybor), "destroy", G_CALLBACK(sens), NULL);
    g_signal_connect(G_OBJECT(okej), "clicked", G_CALLBACK(enter_callback2), player1);
    gtk_widget_show_all(wybor);

}
