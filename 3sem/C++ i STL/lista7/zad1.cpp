#include <iostream>
#include <random>
#include <functional>
#include <algorithm>
#include <chrono>

using namespace std;

static default_random_engine dre;
int N = 5;

template <typename T>
void permutate(T array[]) {
    uniform_int_distribution<int> r(0, N - 1);
    for (int i = 0; i < N; i++) {
        swap(array[i], array[r(dre)]);
    }
}

template <typename T>
void print(T array[]) {
    cout << "[";
    for (int i = 0; i < N - 1; i++) {
        cout << array[i] << ", ";
    }
    cout << array[N - 1] << "]" << endl;
}

int main()
{   
    dre.seed(chrono::system_clock::now().time_since_epoch().count());
    int test1[]{1,2,3,4,5};
    cout << "Before permuation: ";
    print(test1);
    permutate(test1);
    cout << "After permuation: ";
    print(test1);

    string test2[]{"a", "b", "c", "d", "e"};
    cout << "Before permuation: ";
    print(test2);
    permutate(test2);
    cout << "After permuation: ";
    print(test2);
    return 0;
}