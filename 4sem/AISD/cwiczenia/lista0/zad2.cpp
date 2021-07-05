//Piotr Piesiak
//318000
//WJA
#include<iostream>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    int a,b,x = 1;
    cin >> a >> b;
    for (int i = a; i <= b; i += x) {
        if (x == 1 && i % 2021 == 0) {
            cout << i << " ";
            x = 2021;
        }
        else {
            if (x == 2021)
                cout << i << " ";
        }
    }
    return 0;
}