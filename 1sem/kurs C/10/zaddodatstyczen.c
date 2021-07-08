#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char instrukcja[10001];
typedef struct katalog {
    int glebokosc;
    int licznik;
    struct katalog* edges[257];
    struct katalog* ojciec;
} katalog;

int main(void)
{
    katalog *root =(katalog*)calloc(sizeof(katalog),1);
    root->glebokosc=0;
    while(scanf("%s",instrukcja)!=EOF)
        printf("gdaWBD");
    scanf("%[^5]s",instrukcja);
        printf("kupa");
    return 0;
}
