#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
    printf("p1\n");
    time_t tt;
    srand(time(&tt));
    int x=rand()%100;
    printf("%d ",x);
    int y=rand()%100;
    printf("%d\n",x);
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++)
            printf("%d ",rand()%2);
    printf("\n");
    }
return 0;
}
