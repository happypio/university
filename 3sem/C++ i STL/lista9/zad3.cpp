#include<iostream>
#include<regex>

using namespace std;

int main() {
    // ()* <=> {0,} ()+ <=> {1,} \\w letter
    regex village_1("([[:upper:]][[:alpha:]]+)([[:space:]]+[[:upper:]][[:alpha:]]+)*");
    regex village_2("([A-Z][a-z]{1,})-([A-Z][a-z]{1,})");
    string tests[6]{"Polska Wies", "Jeszcze Bardziej Polska     Wies",
    "niezbyt Wies", "Niezla-Wies", "Niezla-Polska-Wies", "Wroclaw"};
    for(string test: tests) {
        cout << test << " ";
        if (regex_match(test, village_1) || regex_match(test, village_2))
            cout << "Argument is in village format" << endl;
        else
            cout << "Wrong format!" << endl;
    }
    return 0;
}