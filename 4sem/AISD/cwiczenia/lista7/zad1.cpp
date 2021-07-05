#include<iostream>
using namespace std;

int main() {
    int n = 10;
    int T[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            T[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int dl = 0; dl < n; dl++) {
        for(int i = 0; i < n - dl; i++) {
            //if (i + dl < n)
            T[i][i + dl] = dl;
            //if (i - dl >= 0)
                //T[i][i - dl] = dl;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
   return 0; 
}