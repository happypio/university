#include<stdio.h>
#include<stdlib.h>


int main(void){
    int c;
    c=getchar();
    while(c != EOF)
    {
        //putchar(c);
        printf("%c",c);
        c=getchar();
    }
    putchar(c);
    return 0;
}
