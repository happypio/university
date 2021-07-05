#include<iostream>
using namespace std;

int g (int x) {
    return x*x;
}

double h ( double x) {
    return x;
}

double f (int a, double y) {
    return (double) a + y;
}


template<typename G_res, typename G_arg, typename H_res, typename H_arg, typename F_res>
class compose_f_gx_hx {
    typedef G_res ( *G )(G_arg);
    typedef H_res ( *H )(H_arg);
    typedef F_res (*F) (G_res, H_res);
    G f_gx;
    H f_hx;
    F f_fx;
    public:
        compose_f_gx_hx(G g , H h, F f) : f_gx(g) , f_hx(h) , f_fx(f) {};
        F_res operator() (G_arg x, H_arg y) {
            return f_fx( f_gx(x) , f_hx(y) );
        }
};

int main() {

    int x1 = 2;
    double x2 = 3.5;

    cout << "x1 = " << x1 << " , x2 = " << x2 << endl;

    cout << "g(x1) = " << g(x1) << " , h(x2) = " << h(x2) << endl;

    cout << "f ( g(x1) , h(x2) ) = " << f( g(x1) , h(x2) ) << endl; 

    compose_f_gx_hx < int, int, double, double, double > compose (g, h, f);

    cout << "wynik compose f ( g(x1) , h(x2) ) = " << compose( x1, x2 ) << endl;

    return 0;
}
