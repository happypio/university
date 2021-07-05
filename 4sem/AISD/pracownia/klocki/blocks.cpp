#include<iostream>
using namespace std;

//Piotr Piesiak, pracownia aisd
//318000

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, s = 0;
    cin >> n;
    int h[n];
    int S[n];
    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        h[i] = x;
        s += h[i];
        S[i] = s;
    }
    
    int dp_tab[2][s+1];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= s; j ++){
            dp_tab[i][j] = -1;
        }
    }
    dp_tab[1][s] = 0; // without elements there are 0-elemetns equal towers
    for (int i = 0; i < n; i ++) {
        //(j - s) is the differenece between two towers
        //so j = 0 means height(tower1) - height(tower2) = -s
        for (int j = (s - S[i]); j <= s; j++) {
            if (j - h[i] >= 0 && dp_tab[(i+1)%2][j - h[i]] != -1 && dp_tab[i % 2][j] < dp_tab[(i+1)%2][j - h[i]] + h[i])
                dp_tab[i % 2][j] = dp_tab[(i + 1) % 2][j - h[i]] + h[i];
            if (j + h[i] <= s && dp_tab[(i+1)%2][j + h[i]] != -1 && dp_tab[i % 2][j] < dp_tab[(i+1)%2][j + h[i]])
                dp_tab[i % 2][j] = dp_tab[(i + 1) % 2][j + h[i]];
            //j + h[i] - s -> difference s - (j + h[i] - s) index of reversed towers -> 2*s - j - h[i]
            if (j + h[i] > s && j + h[i] <= 2*s && dp_tab[(i+1)%2][2*s - j - h[i]] != -1 && dp_tab[i % 2][j] < dp_tab[(i+1)%2][2*s - j - h[i]] + j + h[i] - s)
                dp_tab[i % 2][j] = dp_tab[(i+1)%2][2*s - j - h[i]] + j + h[i] - s;
            if (dp_tab[(i+1)%2][j] != -1 && dp_tab[i % 2][j] < dp_tab[(i+1)%2][j])
                dp_tab[i % 2][j] = dp_tab[(i+1)%2][j];

        }
    }
    for (int i = s; i >= 0; i --) {
        if(dp_tab[(n-1)%2][i] != - 1) {
            if (i == s && dp_tab[(n-1)%2][i] != 0) {
                cout << "TAK\n" << dp_tab[(n-1)%2][i] << "\n";
                break;
            }
            else if(dp_tab[(n-1)%2][i] != 0) {
                cout << "NIE\n" << s - i << "\n";
                break; 
            }
            
        }
    }
    return 0;
}