#include <bits/stdc++.h>
using namespace std;
//Piotr Piesiak, pracownia aisd
//318000

int ans = numeric_limits<int>::max();

int find_set(pair <int, int> vertices[], int x) {
    int parent = vertices[x].second;
    if (parent != x) //we are not in the root
    {
        //path compression
        vertices[x] = make_pair(vertices[x].first, 
                        find_set(vertices, parent));
        return vertices[x].second;
    }
    else 
        return parent;
}

void union_sets(pair <int, int> vertices[], int a, int b) {
    //a , b are sets we want to join
    //ensure that size of a is at least as big as b (if not, swap)
    if (vertices[a].first < vertices[b].first) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    vertices[b] = make_pair(vertices[b].first, a);
    vertices[a] = make_pair(vertices[b].first + vertices[a].first, a);
}

void Kruskal(pair <int, int> vertices[], vector < pair <int, pair <int, int > > > &edges, int n) {
    int taken_edges = 0;
    int i = edges.size() - 1;
    while (i >= 0 && taken_edges < n - 1) {
        pair <int, pair <int, int > > e = edges[i];
        int u = e.second.first,v = e.second.second,w = e.first;
        i--;

        int a = find_set(vertices, u), b = find_set(vertices, v);
        if (a != b) {
            //join two different sets of edges
            union_sets(vertices, a, b);
            taken_edges += 1;
            if (w < ans)
                //update critic edge
                ans = w;

        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,a,b,w;
    cin >> n >> m;
    pair <int, int> vertices[n]; //<size, father>
    for (int i = 0; i < n; i++) {
        vertices[i] = make_pair(1,i);
    }
    vector < pair <int, pair <int, int > > > edges;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        a -= 1; b -= 1;
        edges.push_back(make_pair(w, make_pair(a,b)));
    }
    sort(edges.begin(), edges.end());

    Kruskal(vertices, edges, n); 

    cout << ans << "\n";
    
    return 0;
}