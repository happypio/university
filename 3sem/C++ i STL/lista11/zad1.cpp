#include<iostream>

using namespace std;

template <int n>
struct Lucas {
    static constexpr int value = Lucas<n-1>::value + Lucas<n-2>::value;
    //static const int
};

template <>
struct Lucas<0> {
    static constexpr int value = 2;
};

template <>
struct Lucas<1> {
    static constexpr int value = 1;
};


int main() {
    Lucas <15> l;
    cout << "L(15) = " << l.value << endl;
    return 0;
}