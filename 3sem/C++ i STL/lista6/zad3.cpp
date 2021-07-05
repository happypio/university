#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <utility>
using namespace std;

vector <pair <int, int> > most_frequent(vector<int> v) {
    map <int, int> num_count;
    int count_max = 0;
    for (int i : v) {
        num_count[i]++;
        if (num_count[i] > count_max)
            count_max = num_count[i];
    }
    vector <pair <int,int> > result;
    for (auto it : num_count) {
        if (it.second == count_max)
            result.push_back(make_pair(it.first, it.second));
    }
    return result;
}

int main()
{
    srand (time(NULL));
    vector <int> v {1,1,1,4,4,5,5,5,-1,-1,-1,2,2,100};
    /*vector <int> v(15);
    generate(v.begin(), v.end(), [](){
        return rand()%5;
    });*/
    for (int i : v)
        cout << i << " ";
    cout << endl;
    vector <pair <int,int> > ans = most_frequent(v);
    for (pair<int, int> i : ans)
        cout << i.first << " wystąpił " << i.second << " krotnie " << endl;
}