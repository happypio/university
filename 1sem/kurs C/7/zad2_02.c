#include<stdio.h>
#include<stdlib.h>
#define LL (unsigned long long int)1
size_t maksi = 0;
int szukaj(unsigned long long l, unsigned long long p)
{
    //printf("cos");
     if(l>p)
       return -1;

	 long long sr = l+ (p-l)/2;//(l+p)/2;
     long long *pamiec;
     pamiec = (long long*) malloc (sr);
    if(pamiec==NULL)
        return szukaj(l,sr-1);
    else{
        maksi=sr;
        free(pamiec);
        return szukaj(sr+1,p);
    }
}
int main (void)
{
    szukaj(1,(LL<<62));
    printf("Maksymalna pamiec do zarezerwowania %zu MB\n",maksi/1048576);
  return 0;
}
