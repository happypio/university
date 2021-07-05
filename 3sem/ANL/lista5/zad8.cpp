#include <iostream>
#include <cmath>
using namespace std;

//h(x) = x^5 + x^3 + x - 3
double h (double x) { // h(1) = 0
    return pow(x, 5) + pow(x, 3) + x - 3;
}
//h'(x) = 5x^4 + 3x^2 + 1
double h1 (double x) {
    return 5 * pow(x, 4) + 3 * pow(x, 2) + 1;
}
//h''(x) = 20x^3 + 6x
double h2 (double x) {
    return 20 * pow(x, 3) + 6 * x;
}

//j(x) = x^3 + x^2 - x - 10
double j (double x) { // j(2) = 0
    return x * x * x + x * x - x - 10;
}
//j'(x) = 3x^2 + 2x - 1
double j1 (double x) {
    return 3 * x * x + 2 * x - 1;
}
//j''(x) = 6x + 2
double j2 (double x) {
    return 6 * x + 2;
}

double oliv_met (double x, int n, double (*f)(double), double (*f1)(double), double (*f2)(double)) {
    double xn = x;
    for (int i = 0; i < n; i++) {
        //double ans = xn - f(xn)/f1(xn) - 1.0/2.0 * f2(xn)/f1(xn) * (f(xn)/f1(xn)) * (f(xn)/f1(xn));
        double ans = xn - (pow(f(xn), 2) * f2(xn) + 2.0*f(xn)*pow(f1(xn),2)) / (2.0 * pow(f1(xn) , 3));
        xn = ans;
    }
    return xn;

}

void check_convergence(double x1, double x2, double x3, double x4, double g) {
    cout << "Korzystając z zadania 7, rząd metody wyraża się wzorem:\n"
        << "log ( (x3 - G)/(x2 - G) ) / log ( (x2 - G)/ (x1 - G)\n"
        << "Rząd tej metody: " << log ( abs ( (x4 - g) / (x3 - g) ) ) / log ( abs ( (x3 - g) / (x2 - g) ) ) << endl;
    double e1 = abs(x1 - g);
    double e2 = abs(x2 - g);
    double e3 = abs(x3 - g);
    double e4 = abs(x4 - g);
    cout << "Można też eksperymentalnie:\n"
        << "|x3 - G| / |x2 - G|^P = C , gdzie C powinno być takie samo:\n";
    
    for (double p = 1; p < 5; p ++)
    {
        cout << "P = " << p << endl
        << "c = " << e4 / pow(e3 , p )
        << ", c = " << e3 / pow(e2, p )
        << ", c = " << e2 / pow(e1 , p ) << endl;
    }

}   
int main() {
    double x1 , x2 , x3, x4;
    x4 = oliv_met(5 , 7 , h, h1, h2);
    x3 = oliv_met(5 , 6 , h, h1, h2);
    x2 = oliv_met(5 , 5 , h, h1, h2);
    x1 = oliv_met(5 , 4 , h, h1, h2);
    check_convergence(x1, x2, x3, x4, 1.0);

    cout << "\n\n";
    x4 = oliv_met(5 , 4 , j, j1, j2);
    x3 = oliv_met(5 , 3 , j, j1, j2);
    x2 = oliv_met(5 , 2 , j, j1, j2);
    x1 = oliv_met(5 , 1 , j, j1, j2);
    check_convergence(x1, x2, x3, x4, 2.0);

    
    return 0;
}