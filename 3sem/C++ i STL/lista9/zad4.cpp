#include<iostream>
#include<regex>

using namespace std;

int main() {
    // ()* <=> {0,} ()+ <=> {1,} \\w letter
    //regex complex("(0|([1-9]\\d+))");
    regex complex("\\(( *)-?(0|[1-9](\\d+)?)(.\\d+)?( *)\\+( *)-?(0|[1-9](\\d+)?)(.\\d+)?[iI]( *)\\)");
    string tests[5]{"(20-3i)", "(  -10.5 + -2.3i    )",
    "(0.20 + 2i)", "(00 + -0i)", "(  -3  + 0i   )"};
    for(string test: tests) {
        cout << test << " ";
        if (regex_match(test, complex))
            cout << "Argument is in complex format" << endl;
        else
            cout << "Wrong format!" << endl;
    }
    return 0;
}