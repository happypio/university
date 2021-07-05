#ifndef ruchy_hpp
#define ruchy_hpp
extern GtkWidget *kreski[1000],*gora,*dol,*prawo,*lewo,*skosgl,*skosgp,*skosdl,*skosdp,*kontr1,*pilka;
typedef struct wierzcholek {
        int tab[8];
} wierzcholek;

extern wierzcholek kropki[11][15];
extern int n,plejer,pozx,pozy,single;
extern gint x,y;
void rysuj1();
void rysuj2();
void rysuj3();
void rysuj4();
void rysuj5();
void rysuj6();
void rysuj7();
void rysuj8();
void ustaw_kropki();
extern char *jeden,*drugi;
#endif
