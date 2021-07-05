#include <bits/stdc++.h>
#include <utility>
using namespace std;

//Piotr Piesiak, pracownia aisd
//318000

/*void dfs(int v, vector< pair < int, int > > G[], bool visited[], int w) {
    visited[v] = true;
    for(int i = 0; i < G[v].size(); i++) {
        if(!visited[G[v][i].first] && G[v][i].second >= w) {
            dfs(G[v][i].first, G, visited, w);
        }
    }
}*/

void dfs(int v, vector< pair < int, int > > &G[], bool visited[], int w) {
    stack <int> S;
    S.push(v);
    while (!S.empty()) {
        int p = S.top();
        S.pop();
        visited[p] = true;
            for(int i = 0; i < G[p].size(); i++) {
                if(!visited[G[p][i].first] && G[p][i].second >= w) {
                    S.push(G[p][i].first);
            }
        }
    }
}

bool can_delete(int w, vector< pair < int, int > > &G[], int n) {
    bool visited[n]{};
    dfs(1, G, visited, w);
    //for(int j = 0; j < n; j++)
    //    cout << j << " " << visited[j] << " ";
    //cout << " " << w << endl;
    for(int j = 0; j < n; j++)
        if(!visited[j])
            return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,a,b,w,maksi = 0;
    cin >> n >> m;
    vector< pair < int, int > > G[n];
    vector <int> critic_edges;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        a -= 1; b -= 1;
        G[a].push_back(make_pair(b,w));
        G[b].push_back(make_pair(a,w));
        critic_edges.push_back(w);
        if (w > maksi)
            maksi = w;
    }
    //przyspieszenie: jak binsercz w druga strone to sprawdzic roznice wag

    sort(critic_edges.begin(), critic_edges.end());
    vector<int>::iterator it = unique (critic_edges.begin(), critic_edges.end());
    critic_edges.resize(distance(critic_edges.begin(),it));
    
    if (can_delete(critic_edges[critic_edges.size() - 1], G, n))
        {
            cout << maksi << "\n";
            return 0;
        }
    int l = 0, r = critic_edges.size() - 1, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if (can_delete(critic_edges[mid], G, n))
        {
            l = mid + 1;
            ans = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    //cout << ans << endl;
    if (ans == -1)
        //cout << critic_edges[critic_edges.size() - 1] << '\n';
        cout << maksi << '\n';
    else
        cout << critic_edges[ans] << '\n';
    return 0;
}