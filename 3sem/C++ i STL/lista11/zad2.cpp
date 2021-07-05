#include<iostream>

using namespace std;

template <int n, int k>
struct BinomialCoeff {
    static constexpr int value = (n * BinomialCoeff<n-1, k-1>::value) / k;
    //static const int
};

template <int n>
struct BinomialCoeff<n, 0> {
    static constexpr int value = 1;
};

template <int n>
struct BinomialCoeff<n ,n> {
    static constexpr int value = 1;
};


int main() {
    BinomialCoeff <10, 5> b;
    cout << "Newt(10,5) = " << b.value << endl;
    return 0;
}