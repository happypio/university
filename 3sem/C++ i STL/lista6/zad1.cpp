#include<iostream>
#include <algorithm>
#include <deque>
#include <utility>
using namespace std;

class Person {
    public:
    string name, surname;
    int age, height;
    double weight;
    Person(string n, string s, int a, int h, double w) : name(n),
    surname(s), age(a), height(h), weight(w) {}
    Person() {}
    string toString() {
        return name + " " + surname;
    }

};
deque < Person > people;

void zad_a()
{
    sort(people.begin() , people.end(), [] (Person p1, Person p2){
        double bmi1 = p1.weight / (p1.height/100.0 * p1.height/100.0);
        double bmi2 = p2.weight / (p2.height/100.0 * p2.height/100.0);
        if (bmi1 < bmi2)
            return true;
        return false;
    });

    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.weight / (p.height/100.0 * p.height/100.0) << ", ";
        count++;
    }
    cout << endl;
}

void zad_b()
{
    deque <Person> result (people);
    transform(people.begin(), people.end(), result.begin(), [] (Person p1){
        double w = 0.9*p1.weight;
        Person res(p1.name, p1.surname, p1.age, p1.height, w);
        return res;
    });
    people = result;
    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.weight << ", ";
        count++;
    }
    cout << endl;
}

void zad_c()
{
    partition(people.begin(), people.end(), [] (Person p) {
        return p.weight < 70.0;
    });
    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.weight << ", ";
        count++;
    }
    cout << endl;
}

void zad_d() {
    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.height << ", ";
        count++;
    }
    cout << endl;
    nth_element(people.begin(), people.begin() + 5, people.end(), [] (Person p1, Person p2) {
        return p1.height < p2.height;
    });
    count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.height << ", ";
        count++;
    }
    cout << endl;
}

void zad_e() {
    random_shuffle (people.begin(), people.begin() + 5);
    random_shuffle (people.begin() + 6, people.end());

    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.height << ", ";
        count++;
    }
    cout << endl;
}

void zad_f() {
    auto [min, max] = minmax_element(people.begin(), people.end(), [](Person p1, Person p2) {
        return p1.age < p2.age;
    }) ;
    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() <<" "<< p.height << ", ";
        count++;
    }
    cout << endl;
    cout << "MIN : " << min->name << " " << min->surname << " " << min->age << endl;
    cout << "MAX : " << max->name << " " << max->surname << " " << max->age << endl;
}

int main()
{
    Person a("Jan", "Kowalski", 50, 180, 83.4);
    Person b("Stanisław", "Borowski", 32, 188, 80.2);
    Person c("Maria", "Michalak", 72, 160, 58.1);
    Person d("Krystyna", "Bielecka", 23, 170, 72.4);
    Person e("Anna", "Lewandowska", 55, 171, 77.9);
    Person f("Kazimierz", "Leśniak", 50, 182, 99.9);
    Person g("Andrzej", "Górski", 23, 184, 78.2);
    Person h("Dorota", "Millewska", 30, 170, 60.4);
    Person i("Alicja", "Zając", 44, 180, 75.6);
    Person j("Jolanta", "Stępień", 80, 170, 90.2);
    Person k("Adam", "Zalewski", 12, 165, 59.3);
    people.push_back(a);people.push_back(b);people.push_back(c);people.push_back(d);
    people.push_back(e);people.push_back(f);people.push_back(g);people.push_back(h);
    people.push_back(i);people.push_back(j);people.push_back(k);
    int count = 0;
    for (Person p: people){
        if (count % 4 == 0)
            cout << endl;
        cout << p.toString() << " " << p.weight << " " << p.height << ", ";
        count++;
    }
    cout << endl;
    //zad_a();
    //zad_b();
    //zad_c();
    //zad_d();
    //zad_e();
    //zad_f();
    // compile :
    // g++ -std=c++17 zad1.cpp -o zad1
    return 0;
}