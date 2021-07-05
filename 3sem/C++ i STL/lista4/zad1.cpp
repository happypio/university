#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<ctime>
#include<algorithm>
#include<string>
using namespace std;

vector < double > v;
list < string > l;
set < int > s;

template <int a, int b>
void print_a(int i) {
     if (i > a && i < b)
            cout << i << " "; 
}

void fill() {
    for (int i = 0; i < 10; i++){
        v.push_back ( rand() % 100);
        string s_r = "";
        for (int i = 0; i < (rand() % 10) + 1; i++)
            s_r += (char) (rand() % 26) + 65;
        l.push_back(s_r);
        s.insert(rand() % 100);
        
    }
    //print all
    cout<<"VECTOR: ";
    for_each(v.begin(), v.end(), print_a <-10,120>);
    cout<<endl;
    cout<<"LIST: ";
    for_each(l.begin(), l.end(), [] (string s) {
        cout<<s<<" , ";
    });
    cout<<endl;
    cout<<"SET: ";
    for_each(s.begin(), s.end(), print_a <-10,120>);
    cout<<endl;
}

void a() {

    const int a = 20;
    const int b = 60;
    cout<<"PRINTING VECTOR a = "<<a<<" b = "<<b<<":\n";
    for_each(v.begin(), v.end(), print_a <a,b>);
    cout<<endl;
    string as = "C";
    string bs = "R";
    cout<<"PRINTING LIST as = "<<as<<" bs = "<<bs<<":\n";
    for_each(l.begin(), l.end(), [as,bs] (string s) {
        if (as < s && s < bs)
            cout<<s<<" ";
    });
    cout<<endl;
    cout<<"PRINTING SET a = "<<a<<" b = "<<b<<":\n";
    for_each(s.begin(), s.end(), print_a <a,b>);
    cout<<endl;
}

//jak przeniesc w template string
//czy da sie template na lambdzie zrobic
//jak do funkcji jednoargumentowej przekazac
//inna zmienna inaczej jak template (tak jak w lambdzie robimy to za pomoca [])
void b() {
    const int k = 2;
    const int p = 3;
    int act = 0;
    cout<<"k = "<<k<<" p = "<<p<<endl;
    auto lambda_i = [k,p,&act](int i){
        if (act >= p && (act - p) % k == 0)
            cout<<i<<" ";
        act++;
    };
    auto lambda_s = [k,p,&act](string i){
        if (act >= p && (act - p) % k == 0)
            cout<<i<<" ";
        act++;
    };
    cout<<"PRINTING VECTOR:\n";
    for_each(v.begin(), v.end(), lambda_i);
    cout<<endl;
    act = 0;
    cout<<"PRINTING LIST:\n";
    for_each(l.begin(), l.end(), lambda_s);
    act = 0;
    cout<<endl;
    cout<<"PRINTING SET:\n";
    for_each(s.begin(), s.end(), lambda_i);
    cout<<endl;

}

class Average {
    private:
        int theSum;
        int elem;
    public:
        Average() : theSum {0}, elem {0} {}
        void operator() (int elem) {
            this->theSum += elem;
            this->elem += 1;
        }
        double ans() {
            return (( (double) theSum) / ((double) elem));
        }
};

void c(){
    Average v_a;
    for_each(v.begin(),v.end(),[&v_a](int i){ v_a(i); });
    Average ans = for_each(v.begin(),v.end(),v_a);
    cout<<"VECTOR MOD. = " << ans.ans() << endl;
    cout<<"VECTOR AVG. = "<<v_a.ans()<<endl;
    Average s_a;
    for_each(s.begin(),s.end(),[&s_a](int i){ s_a(i); });
    cout<<"SET AVG. = "<<s_a.ans()<<endl;
}

template<typename T1, T1 mini, T1 maxi>
class MinMax {
    private:
        T1 minn;
        T1 maxx;
    public:
        MinMax() : minn {mini}, maxx {maxi} {}
        void operator() (T1 elem) {
            if(minn == mini || maxx == maxi) {
                minn = elem;
                maxx = elem;
            }
            if (elem < minn)
                minn = elem;
            if (elem > maxx)
                maxx = elem;
        }
        void ans(){
            cout<<"min: "<<minn<<" max: "<<maxx<<endl;
        }
};

//template <string* str >

void d(){
    MinMax <int,0,0> v_m;
    for_each(v.begin(),v.end(),[&v_m](int i){ v_m(i); });
    cout<<"VECTOR: ";
    v_m.ans();
    string mini = "";
    string maxi = "";
    for_each(l.begin(),l.end(),[&mini,&maxi](string elem){
        if(mini == "" || maxi == "") {
                mini = elem;
                maxi = elem;
            }
            if (elem < mini)
                mini = elem;
            if (elem > maxi)
                maxi = elem;
    });
    cout<<"LIST: min: "<<mini<<" max: "<<maxi<<endl;
    MinMax <int,0,0> s_m;
    for_each(s.begin(),s.end(),[&s_m](int i){ s_m(i); });
    cout<<"SET: ";
    s_m.ans();
}

void e(){
    int s_i = 0;
    string s_s = "";
    auto sum_i = [&s_i] (int e){
        s_i += e;
    };
    auto sum_s = [&s_s] (string e){
        s_s += e;
    };
    cout<<"SUM VECTOR:\n";
    for_each(v.begin(), v.end(), sum_i);
    cout<<s_i;
    cout<<endl;
    s_i = 0;
    cout<<"SUM LIST:\n";
    for_each(l.begin(), l.end(), sum_s);
    cout<<s_s;
    cout<<endl;
    cout<<"SUM SET:\n";
    for_each(s.begin(), s.end(), sum_i);
    cout<<s_i;
    cout<<endl;
}

int main() {

    srand( time( NULL ) );
    fill();
    cout<<"\na)\n";
    a();
    cout<<"\nb)\n";
    b();
    cout<<"\nc)\n";
    c();
    cout<<"\nd)\n";
    d();
    cout<<"\ne)\n";
    e();
    cout<<"\n";
    
    return 0;
}