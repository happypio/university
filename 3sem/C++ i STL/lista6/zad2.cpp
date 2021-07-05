#include<iostream>
#include <algorithm>
#include <list>
#include <ctime>
#include <cstdlib>

using namespace std;

class Point {
    public:
    int x,y,r,g,b;
    string name;
    Point() {}
    Point(int x, int y, int r,int g, int b, string n) : x(x), y(y), r(r), g(g), b(b), name(n) {}
    string toString() {
        return name;
    }
};
Point _;
list <Point> l(17,_);

void print(){
    for(Point p : l){
        cout << p.toString() << " " << p.x << " " << p.y << " " << 0.3*p.r + 0.59*p.g + 0.11*p.b << endl;
    }
}

void zad_a() {
    l.remove_if([](Point p){
        return p.name.length() > 5;
    });
    print();
}

void zad_b() {
    int xs = 1;
    int ys = 1;
    auto lambda = [&xs, &ys](Point p) {
        return p.x * xs > 0 && p.y * ys > 0;
    };
    int q1 = count_if(l.begin(), l.end(), lambda);
    cout << "Ćwiartka 1: " << q1 << " ";
    xs = -1; ys = 1;
    int q2 = count_if(l.begin(), l.end(), lambda);
    cout << "Ćwiartka 2: " << q2 << " ";
    xs = -1; ys = -1;
    int q3 = count_if(l.begin(), l.end(), lambda);
    cout << "Ćwiartka 3: " << q3 << " ";
    xs = 1; ys = -1;
    int q4 = count_if(l.begin(), l.end(), lambda);
    cout << "Ćwiartka 4: " << q4 << " " << endl;
}

void zad_c() {
    //nie da sie sort(l.begin(), l.end() , lambda... ?)
    /*sort(l.begin(), l.end(), [](Point p1, Point p2) {
        double t1 = 0.3*p1.r + 0.59*p1.g + 0.11*p1.b;
        double t2 = 0.3*p2.r + 0.59*p2.g + 0.11*p2.b;
        return t1 < t2;
    });*/
    l.sort([](Point p1, Point p2) {
        double t1 = 0.3*p1.r + 0.59*p1.g + 0.11*p1.b;
        double t2 = 0.3*p2.r + 0.59*p2.g + 0.11*p2.b;
        return t1 < t2;
    });
    print();
}

void zad_d() {
    int good_points = count_if(l.begin(), l.end(), [] (Point p1) {
        return 0.3*p1.r + 0.59*p1.g + 0.11*p1.b < 64;
    });
    cout << "Ciemnych punktów: " << good_points << endl;
    list < Point > good_list(good_points, _);
    copy_if(l.begin(), l.end(), good_list.begin(), [] (Point p1) {
        return 0.3*p1.r + 0.59*p1.g + 0.11*p1.b < 64;
    });
    cout << "\nWypisanie ciemnych punktów:" << endl;
    for (Point p : good_list) {
        cout << p.toString() << " " << p.x << " " << p.y << " " << 0.3*p.r + 0.59*p.g + 0.11*p.b << endl;
    }


}

int main() {
    srand (time(NULL));
    generate(l.begin(), l.end(), [](){
        string name = "";
        name += (char) (rand()%26 + 65); // + 'A';
        int length = rand()%10;
        for(int i = 0; i < length; i ++)
            name += (char) (rand()%26 + 65);
        Point p(rand()%100 - 50,rand()%100 - 50,rand()%256, rand()%256, rand()%256,name);
        return p;
    });
    print();
    cout << endl;
    zad_a();
    zad_b();
    zad_c();
    zad_d();
    return 0;
}