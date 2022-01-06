#include<stdio.h>
#include<string.h>
#define PRINTBIN(napis) \
    do { \
    int unsigned dlugosc=0;\
    const char s[] = #napis;\
    while(dlugosc<strlen(s)){\
        dlugosc+=8;\
    }\
    int potega=7;\
    int litera=0;\
    for(int unsigned i=0;i<dlugosc-strlen(#napis);i++)\
        potega--;\
    for(int unsigned i=0;i<strlen(#napis);i++){\
            int a=#napis[i]-'0';\
            litera=litera+(a<<potega);\
            potega--;\
            if(potega<0){\
                char c=litera;\
                printf("%c",c);\
                litera=0;\
                potega=7;\
            }\
        }\
} while(0);
int main(void)
{
    for (int i=0; i < 10; i++){
        if (i%2==0){
            PRINTBIN(111010001011010010100100001010);
        }
        else{
            PRINTBIN(1010);}
}
    PRINTBIN(11000010110001001100011);
    return 0;
}
