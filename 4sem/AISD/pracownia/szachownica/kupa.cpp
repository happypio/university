#include <bits/stdc++.h>
using namespace std;

int main()
{
    double a = 0;
    for (int i = 21; i > 0; i--) {
        double x = 1, k = 387;
        for (double j = 364; j >= 364 - i; j--) {
            x *= (j/k);
            k--;
        }
        x *= 23*22;
        double tmp = 21;
        while (k >= 366){
            x *= (tmp/k);
            tmp --;
            k--;
        }
        a += x;
    }
    cout << a << endl;
    return 0;

}