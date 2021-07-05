#include<iostream>

using namespace std;

template <int a, int b>
struct GCD {
    static constexpr int value = GCD<b, a % b>::value;
    //static const int
};

template <int a>
struct GCD<a, 0> {
    static constexpr int value = a;
};


int main() {
    GCD <72, 27> gcd;
    cout << "GCD(10,5) = " << gcd.value << endl;
    return 0;
}