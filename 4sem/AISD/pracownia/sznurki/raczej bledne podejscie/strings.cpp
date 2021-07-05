#include<bits/stdc++.h> 
using namespace std;
int act_size;
class Pair {
    public:
    Pair *bef, *nxt;
    pair <int,int> e;
    Pair(Pair *b, Pair *n, pair <int, int> el) {
        bef = b; nxt = n; e = el; 
    }
};

bool compp(pair <int, int> a, pair <int, int> b) {
    if (a > b) return true;
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    int m,d,n;
    Pair *beg, *end, *act;
    cin >> m;
    act_size = m;
    vector <pair <int, int> > strings;
    for (int i = 0; i < m; i++) {
        cin >> d >> n;
        strings.push_back(make_pair(d,n));
    }
    sort(strings.begin(),strings.end(), compp);
    for (int i = 0; i < m; i++) {
        cout << strings[i].first << " " << strings[i].second << endl;
        if (i == 0) {
            Pair c = Pair(NULL, NULL, strings[i]);
            beg = &c;
            end = beg;
        } else {
            Pair c = Pair(NULL, NULL, strings[i]);
            act = &c;
            Pair *tmp = end;
            end = act;
            tmp->nxt = end;
            end->bef = tmp;
        }
    }
    act = beg;
    int x = 0;
    while (act != NULL && x < 3) {
        cout << act->e.first << " " << act->e.second << endl;
        act = act->nxt;
        x++;
    }

    //while (x < m) {
        //schodzimy w dol, gdy natkniemy sie ze n >=2 to laczymy i shift_upujemy
        //gdy po zlaczeniu n = 0 to wstawiamy w te dziure element z konca
        //moze w momencie wstawiania nowego najpierw sprawdzic czy taki klucz istnieje i potem shift_up
    //}
    return 0;
}