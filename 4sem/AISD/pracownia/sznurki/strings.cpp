#include<iostream>
#include<utility>
using namespace std;
typedef long long ll;

void merge(pair <ll, ll> K[], int l, int m, int r) {
    pair <ll, ll> L[m - l + 1],R[r - m];

    for (int i = l; i <= m; i++) {
        L[i - l] = K[i];
    }
    for (int i = m + 1; i <= r; i++) {
        R[i - m - 1] = K[i];
    }
    int i = 0, j = 0, k = 0;

    while (i < m - l + 1 && j < r - m) {
        if (L[i] < R[j]) {
            K[l + k] = L[i];
            i++;
        }
        else {
            K[l + k] = R[j];
            j++;
        }
        k++;
    }
    for (;i < m - l + 1; i++) {
        K[l + k] = L[i];
        k++;
    } 
    for (;j < r - m; j++){
        K[l + k] = R[j];
        k++;
    }
}

void merge_sort(pair <ll, ll> K[], int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    merge_sort(K, l, m);
    merge_sort(K, m + 1, r);
    merge(K, l, m, r);
}

int bin_search(pair <ll, ll> K[], int l, int r, ll v) {
    int m;
    if (K[r].first < v || K[l].first > v)
        return -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (K[m].first == v)
            return m;
        if (K[m].first < v) 
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

//we can simulate game backward, remembering not to join to much (72 line)
//proof by induction
ll solve(pair <ll, ll> K[], int n) {
    ll res = 0;
    for (int i = 0; i < n; i++) {
        if(K[i].second % 2 != 0)
        {
            K[i].second--;
            res++;
        }
        if(K[i].second > 1) {
            ll new_d = K[i].first, new_n = K[i].second, s;
            new_d *= 2; new_n /= 2;
            if (i + 1 < n && K[i + 1].first == new_d)
                s = i + 1;
            else
                s = bin_search(K, i + 1, n - 1, new_d);
            if (s != -1) {
                K[s].second += new_n;
            }
            else {
                K[i] = make_pair(new_d, new_n); 
                i--;
            }
        }
        
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m,n,d;
    cin >> m;
    pair <ll, ll> strings[m];
    for (int i = 0; i < m; i++) {
        cin >> d >> n;
        strings[i] = make_pair(d,n);
    }
    merge_sort(strings, 0, m - 1);
    cout << solve(strings, m) << "\n";
    return 0;
}