#include <iostream>
#include <cmath>

using namespace std;

void check_convergence ( double e1, double e2, double e3, double e4) {
    for (double p = 1; p < 5; p ++)
    {
        cout << "P = " << p << endl
        << "c = " << e4 / pow(e3 , p )
        << ", c = " << e3 / pow(e2, p )
        << ", c = " << e2 / pow(e1 , p ) << endl;
    }
}

int main() {
    double r1 = 0.763907023;
    double r2 = 0.543852762;
    double r3 = 0.196247370;
    double r4 = 0.009220859;

    double a1 = 0.605426053;
    double a2 = 0.055322784;
    double a3 = 0.004819076;
    double a4 = 0.000399783;
    cout << "|x_n - G| / |x_(n-1) - G|^P = C , gdzie C powinno być takie samo:\n";
    cout << "\nZbieżnoś dla metody Rosjan:\n";

    check_convergence(r1, r2, r3, r4);

    cout << "\nZbieżnoś dla metody Amerykanów:\n";

    check_convergence(a1, a2, a3, a4);

    cout << "Zbieżność metody Rosjan to 3, a Amerykanów to 1!\n";
    return 0;
}