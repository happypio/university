#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

long double const g = 0.5772156649;
long double const e = 2.7182818284;

complex<long double> gamma_Euler(complex<long double> z, int n) {
    complex<long double> ans(complex<long double>(1.0,0.0) / z);
    complex<long double> product(1.0,0);
    for (int i = 1; i <= n; i++) {
        product *= complex<long double>(pow(1.0 + 1.0/i, z)) / (complex<long double>(1.0,0.0) + z/complex<long double>(i,0.0));
    }
    return product*ans;
}
complex<long double> inv_gamma_Euler(complex<long double> z, int n) {
    complex<long double> ans(z * pow(e, complex<long double>(g,0) * z));
    complex<long double> product(1.0,0);
    for (int i = 1; i <= n; i++) {
        product *= (complex<long double>(1.0,0) + z / complex<long double>(i,0)) *
        pow(e, - z/complex<long double>(i,0));
    }
    return ans * product;
}
int main()
{
    complex<long double> c1 (2.5, 0); 
    //expected ~1.32
    cout << real(gamma_Euler(c1, 300)) << " + " << imag(gamma_Euler(c1, 300)) << "i" << "\n";
    complex<long double> c2 (2.5, 3.0); 
    //expected -0.21 + 0.07i
    cout << real(gamma_Euler(c2, 300)) << " + " << imag(gamma_Euler(c2, 300)) << "i" << "\n";
    //expected -0.76
    cout << real(inv_gamma_Euler(c1, 300)) << " + " << imag(inv_gamma_Euler(c1, 300)) << "i" << "\n";
    //expected -4.1 - 1.4i
    cout << real(inv_gamma_Euler(c2, 300)) << " + " << imag(inv_gamma_Euler(c2, 300)) << "i" << "\n";
    return 0;
}