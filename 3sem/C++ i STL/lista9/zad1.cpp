#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char const *argv[]) {
    // [a-b] - number from interval
    // | alternative, ()? 0 or 1 occurences
    regex time("([0-1]\\d|2[0-3]):[0-5]\\d(:[0-5]\\d)?");
    if (argc > 1) {
        cout << argv[1] << endl;
        if (regex_match(argv[1], time))
            cout << "Argument is in time format" << endl;
        else
            cout << "Wrong format!" << endl;
    }
    return 0;
}