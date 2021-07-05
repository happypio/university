#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <list>

using namespace std;

class Graph {
    private:
        int size;
        map < string, int > m_string;
        map < int, string > m_int;
        vector < list < pair < int, int > > > G;
    public:
    Graph() : size(0) {}
    void add_vertex(int v, string name) {
        if (v > size) {
            for (int i = size; i <= v; i++)
                G.push_back(list < pair < int, int > >() );
            size = v;
        }
        m_string[name] = v;
        m_int[v] = name;

    }
    void delete_vertex(int v){
        list < pair < int, int > > neighbours;
        for (auto it = G[v].begin(); it != G[v].end(); it ++) {
            neighbours.push_back(make_pair(it->first, it->second ) );
        }
        for (auto it = neighbours.begin(); it != neighbours.end(); it ++) {
            delete_edge(it->second, v, it->first);
        }


    }
    void delete_vertex (string s){
        int v = m_string[s];
        delete_vertex(v);
    }

    void add_edge(int w, int v1, int v2){
        G[v1].push_back( make_pair(v2, w));
        if(v1 != v2)
            G[v2].push_back( make_pair(v1, w));
    }
    void add_edge(int w, string s1, string s2){
        int v1 = m_string[s1];
        int v2 = m_string[s2];
        add_edge(w,v1,v2);
    }
    void delete_edge(int w, int v1, int v2){
        G[v1].remove( make_pair (v2, w) );
        if (v1 != v2)
            G[v2].remove( make_pair (v1, w) );
    }
    void delete_edge(int w, string s1, string s2){
        int v1 = m_string[s1];
        int v2 = m_string[s2];
        delete_edge(w, v1, v2);
    }
    void change_edge(int w, int new_w, int v1, int v2){
        G[v1].remove( make_pair (v2, w) );
        G[v1].push_back( make_pair(v2, new_w));
        if (v1 != v2) {
            G[v2].remove( make_pair (v1, w) );
            G[v2].push_back( make_pair(v1, new_w));
        }
    }
    void change_edge(int w, int new_w, string s1, string s2){
        int v1 = m_string[s1];
        int v2 = m_string[s2];
        change_edge(w, new_w, v1, v2);
    }
    void print_vertex(int v){
        cout << "EDGES(NAMES) AND WEIGHTS of " << v << "(" << m_int[v] << "): \n";
        for (auto it = G[v].begin(); it != G[v].end(); it ++) {
            cout << it->first << "(" << m_int[it->first] << ") " 
            << it->second << endl;
        }
    }
    void print_vertex(string s){
        print_vertex(m_string[s]);
    }

    void dfs(int vertex, bool path[] ) {
        path[vertex] = 1;
        for (auto it = G[vertex].begin(); it != G[vertex].end(); it ++) {
            if(!path[it->first])
                dfs(it->first, path);
        }
    }

    bool exists_path(int v1, int v2){
        bool path[this->size + 1] = {0};
        dfs(v1, path);
        return path[v2];

    }
    bool exists_path(string s1, string s2){
        return exists_path(m_string[s1], m_string[s2]);
    }

};

int main() {

    Graph g = Graph();
    g.add_vertex(3,"tablica");
    g.add_vertex(1, "zmywarka");
    g.add_vertex(2, "drugi");
    g.add_vertex(5, "piaty");
    g.add_vertex(6, "szosty");
    g.add_vertex(10, "plyn");

    g.add_edge(10, 1, 3);
    g.add_edge(-4, "piaty", "plyn");
    g.add_edge(7, 5, 3);
    g.add_edge(2, "szosty", "drugi");
    g.add_edge(88, "drugi", "drugi");
    g.add_edge(91, 6, 2);
    g.add_edge(44, 10, 2);

    g.print_vertex(3);
    g.print_vertex(2);
    g.print_vertex(5);

    cout << '\n' << "Delete edge 2<->6 weigth:91 and update 1<->3 weigth:123 \n\n";
    g.delete_edge(91, "drugi", "szosty");
    g.change_edge(10, 123, 1, 3);

    g.print_vertex(3);
    g.print_vertex(2);
    g.print_vertex(5);

    cout << "\nDelete 10 vertex \n\n";
    g.delete_vertex(10);
    g.print_vertex(10);
    g.print_vertex(5);
    g.print_vertex(2);

    cout<< "\nIs there a path from 1 to 5? \n\n";
    cout << g.exists_path(1,5) << endl;

    cout<< "\nIs there a path from 1 to 2? \n\n";
    cout << g.exists_path(1,2) << endl;

    cout << "\nAdding vertex 10 and edge 10<->2 , 5<->10 \n";
    g.add_vertex(10, "dziesiaty");
    g.add_edge(1, 2, 10);
    g.add_edge(0, 10, 5);

    cout<< "\nIs there a path from 1 to 2? \n\n";
    cout << g.exists_path(1,2) << endl;

    g.print_vertex(3);
    g.print_vertex(2);
    g.print_vertex(5);



    return 0;
}