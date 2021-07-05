#ifndef funkcje_h
#define funkcje_h
enum typfig{Trojkat, Kolo, Kwadrat};
typedef struct Figura{
    enum typfig figura;
    float x;
    float y;
    float x1;
    float y1;
    float wymiar;
}Figura;

extern Figura *t[100];
Figura *nowy_kwadrat(float x,float y,float wymiar);
Figura *nowy_trojkat(float x,float y,float x1,float y1,float wymiar);
Figura *nowe_kolo(float x,float y,float wymiar);
float modul(float a);
float pole (Figura *f);
void przesun(Figura *f,float x,float y);
float sumapol(int size);
#endif
