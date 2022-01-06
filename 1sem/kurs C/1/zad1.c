#include<stdio.h>
#include<math.h>

int main(void)
{
    double z,licznik=1.0;
    long int licz=2;
    double dzeta,suma;
    scanf("%lf",&z);
    suma=pow(licznik,z);
    dzeta=0;
    licznik++;
    while(suma>dzeta)
    {
        dzeta=suma;
        suma += 1.0/pow(licznik,z);
        //printf("%lf \n",dzielenie);
        licznik++;
        licz++;
    }
    printf("%lf %ld",suma,licz);
    return 0;
}
