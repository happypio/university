#ifndef obsluga_hpp
#define obsluga_hpp
extern const gchar *gracz1,*gracz2;
void czyszczenie_ekranu();
void nowy_przycisk(gint x, gint y,gint sz, gint wy, GtkWidget *przycisk, GtkWidget *gdzie);
void ustaw_okno(const gchar *title, gint x, gint y, gint kont,GtkWidget *okienko);
void wybor_graczy2();
void wroc();
void sens();
void wychodzenie();
void wybor_graczy();
#endif
