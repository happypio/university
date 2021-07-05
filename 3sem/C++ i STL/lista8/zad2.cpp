#include<iostream>
#include<complex>
#include<cmath>
#include<fstream>
using namespace std;
#define M_PI 3.14159265358979323846
complex<long double> dzeta_Riemann(complex <long double> z, int n) {
    complex <long double> ans(0.0, 0.0);
    for (int i = 1; i <= n; i++) {
        ans += pow(1.0/i, z);
    }
    return ans;
}
complex<long double> gamma_Euler(complex<long double> z, int n) {
    complex<long double> ans(complex<long double>(1.0,0.0) / z);
    complex<long double> product(1.0,0);
    for (int i = 1; i <= n; i++) {
        product *= complex<long double>(pow(1.0 + 1.0/i, z)) / (complex<long double>(1.0,0.0) + z/complex<long double>(i,0.0));
    }
    return product*ans;
}
complex<long double> dzeta_Riemann_b(complex <long double> z, int n) {
    complex<long double> ans(0.0,0.0);
    cout << real(z) << endl;
    if (real(z) >= 0.8)
        return dzeta_Riemann(z, n);
    else
        return pow(2,z) * pow (M_PI, z - complex<long double>(1.0,0.0)) * sin(complex<long double>(M_PI,0.0)*z/complex<long double>(2.0,0.0))*
        gamma_Euler(complex<long double>(1.0,0.0)-z,n)*dzeta_Riemann_b(complex<long double>(1.0,0.0)-z, n);
}
void critical_line() {
    ofstream file;
    file.open("plot.csv");
    for (int i = -60; i <= 60; i++)
    {
        complex<long double> c (0.5, i);
        file << i << "," << real(dzeta_Riemann_b(c, 1000)) 
            << "," << imag(dzeta_Riemann_b(c, 1000)) << endl;   
    }
    file.close();
}
int main()
{
    complex<long double> c1 (2.5, 0);
    cout << real(dzeta_Riemann(c1, 1000)) << " + " << imag(dzeta_Riemann(c1, 1000)) << "i" << "\n";
    complex<long double> c2 (2.5, 3.0);
    cout << real(dzeta_Riemann(c2, 1000)) << " + " << imag(dzeta_Riemann(c2, 1000)) << "i" << "\n";
    complex<long double> c3 (0.5, 3.0);
    cout << real(dzeta_Riemann(c3, 1000)) << " + " << imag(dzeta_Riemann(c3, 1000)) << "i" << "\n";
    critical_line();
    return 0;
}