#include<iostream>
using namespace std;

int main()
{
    int *wskaznik;
    wskaznik = new int [10];
    cout<<*(wskaznik+1)<<" "<<wskaznik[1]<<" "<<wskaznik<<" "<<wskaznik++;
    return 0;
}
