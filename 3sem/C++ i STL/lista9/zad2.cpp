#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char const *argv[]) {
    // [a-b] - number from interval
    // | alternative, ()? 0 or 1 occurences
    regex date_0("((0[1-9]|2[0-8]|1\\d)-(02)-(\\d{3}[1-9]|\\d{2}[1-9]\\d|\\d[1-9]\\d{2}|[1-9]\\d{3}))");
    regex date_1("((0[1-9]|30|[12]\\d)-(0[469]||11)-(\\d{3}[1-9]|\\d{2}[1-9]\\d|\\d[1-9]\\d{2}|[1-9]\\d{3}))");
    regex date_2("((0[1-9]|3[01]|[12]\\d)-(0[13578]|1[02])-(\\d{3}[1-9]|\\d{2}[1-9]\\d|\\d[1-9]\\d{2}|[1-9]\\d{3}))");
    if (argc > 1) {
        for(int i = 1; i < argc; i++)
        {
            cout << argv[i] << " ";
            if (regex_match(argv[i], date_0) || regex_match(argv[i], date_1) || regex_match(argv[i], date_2))
                cout << "Argument is in date format" << endl;
            else
                cout << "Wrong format!" << endl;
        }
    }
    return 0;
    // tests:
    // ./zad2 01-01-0001 01-01-0000 29-02-2003 28-02-2003 31-08-1002 31-09-2020 31-12-2000
}