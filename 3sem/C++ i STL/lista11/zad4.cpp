#include <iostream>
using namespace std;

template <size_t N, typename T>
struct dotProduct
{
    static constexpr T result(T *a, T *b)
    {
        return *a * *b + dotProduct<N - 1, T>::result(a + 1, b + 1);
        // iterating through a and b array by adding 1 to pointer
    }
};

template <typename T>
struct dotProduct<0, T>
{
    static constexpr T result(T *a, T *b)
    {
        return T{};
    }
};

int main() {
    int t1[4] = {1, 2, 3, 4};
    int t2[4] = {4, 3, 2, 1}; // dotProduct = 20
    cout << "dotProduct: " << dotProduct<4, int>::result(t1, t2) << endl;
    return 0;
}