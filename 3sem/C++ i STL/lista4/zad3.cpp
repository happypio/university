#include<iostream>
using namespace std;

class f1 : public unary_function< int, int > {
    public:
        int operator()(int x) {
            cout << "f1 " << x << endl;
            return x;
        }
};

class f2 : public unary_function< int , void > {
    public:
        void operator()(int x) {
            cout << "f2 " << x << endl;
        }
};

class f3 : public unary_function< int , char > {
    public:
        char operator()(int x) {
            cout << "f3 " << x << endl;
            return 'c';
        }
};

class f4 : public unary_function< int , double > {
    public:
        double operator()(int x) {
            cout << "f4 " << x << endl;
            return 2.0;
        }
};

class f5 : public unary_function< int , string > {
    public:
        string operator()(int x) {
            cout << "f5 " << x << endl;
            return "aaa";
        }
};

template< typename F1, typename F2 >
class in_sequence_c : public unary_function< typename F1::argument_type , void > {
   typedef typename F1::argument_type arg_type;
   F1 f1;
   F2 f2;
    public:
        in_sequence_c(F1 f_1, F2 f_2) : f1(f_1), f2(f_2) {};
        void operator() (arg_type x) {
            f1(x);
            f2(x);
        }
};

template< typename F1, typename F2 >
in_sequence_c< F1, F2> in_sequence(F1 f1, F2 f2) {
    return in_sequence_c < F1 , F2 > (f1,f2);
}
int main() {

    in_sequence ( f1() , f2() )(1);
    cout << "\n";
    in_sequence ( in_sequence ( f1() , f2() ) , in_sequence ( f3() , f4() ) )(2);
    cout << "\n";
    in_sequence ( in_sequence (in_sequence ( f1() , f2() ) , in_sequence ( f3() , f4() ) ) , f5() )(3);
    return 0;
}