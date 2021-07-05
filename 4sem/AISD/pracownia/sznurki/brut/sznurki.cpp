//Zadanie A
//Piotr Piesiak 318000 10.03.2021
#include<bits/stdc++.h> 
using namespace std;
long long int act_size;
vector <pair <long long int, long long int> > K;

void shift_down(long long int i) {
    long long int k = i, j;
    do {
        j = k;
        if (2*j <= act_size && K[2*j].first > K[k].first)
            k = 2*j;
        if (2*j + 1 <= act_size && K[2*j + 1].first > K[k].first)
            k = 2*j + 1;
        pair <long long int, long long int> tmp = K[j];
        K[j] = K[k];
        K[k] = tmp;
    } while(j != k);
}

void shift_up(long long int i) {
    long long int k = i, j;
    do {
        j = k;
        if (j > 1 && K[j / 2].first < K[k].first)
            k = j / 2;
        pair <long long int, long long int> tmp = K[j];
        K[j] = K[k];
        K[k] = tmp;
    } while (j != k);
}

pair <long long int, long long int> delete_max() {
    pair <long long int, long long int> ans;
    ans = K[1];
    K[1] = K[act_size];
    K.pop_back();
    act_size--;
    shift_down(1);
    return ans;
}

void insert(pair<long long int, long long int> u) {
    act_size ++;
    K.push_back(u);
    shift_up(act_size);
}

long long int reduce(pair <long long int, long long int> a) {
    long long int x = a.second - 2, p = 2;
    while(x > 1) {
        x -= p;
        p *= 2;
    }
    if (x < 0)
        p /= 2;
    return p;
}

vector <pair <long long int, long long int> > update(vector <pair <long long int, long long int> > vertices) {
    for(long long unsigned int i = 0;i < vertices.size(); i++) {
        insert(vertices[i]);
    }
    vector <pair <long long int, long long int> > a;
    return a;
}

long long int solve() {
    long long int lenght_bef = 0;
    vector <pair <long long int, long long int> > vertices;
    while(act_size > 0) {
        pair <long long int, long long int> x = delete_max();
        //cout << x.first << " " << x.second << endl;
        if (x.first == lenght_bef) {
            pair <long long int, long long int > tmp = vertices[vertices.size() - 1];
            vertices.pop_back();
            x = make_pair(x.first, x.second + tmp.second);
        }
        if (x.second >= 2) {
            long long int t = reduce(x);
            //cout << t << endl;
            pair <long long int, long long int> new_x = make_pair(t * x.first, 1);
            vertices.push_back(new_x);
            if (x.second - t > 0) {
                vertices.push_back(make_pair(x.first, x.second - t));
            }
            vertices = update(vertices);
        } else {
            vertices.push_back(x);
        }
        lenght_bef = x.first;
    }
    //for (int i = 0; i < vertices.size(); i++) {
    //    cout << vertices[i].first << " " << vertices[i].second << endl;
    //}
    return vertices.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    long long int m,d,n;
    cin >> m;
    act_size = m;
    //array has to be bigger than m
    K.push_back(make_pair(0,0));
    for (long long unsigned int i = 1; i <= m; i++) {
        cin >> d >> n;
        pair <long long int, long long int> p = make_pair(d,n);
        K.push_back(p);
    }
    //building a heap
    //cout << K.size() << " " << act_size << endl;
    for (long long unsigned int i = m / 2; i >= 1; i--) {
        shift_down(i);
    }

    //for (int i = 1; i <= m; i++) {
    //    cout << K[i].first << " " << K[i].second << endl;
    //}
    
    cout << solve() << "\n";
    return 0;
}