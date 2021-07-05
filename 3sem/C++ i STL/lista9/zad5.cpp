#include <iostream>
#include <regex>
#include <string>
#include <fstream>
using namespace std;

void search_hyperlinks(string file, regex reg) {
    ifstream f;
    string line;
    f.open(file);
    while( getline(f,line)) {
        smatch m;
        while (regex_search(line, m, reg)) {
            cout << m.str(m.size() - 1) << endl;
            line = m.suffix().str();
        }
    }
    f.close();
}

int main() {
    // ()* <=> {0,} ()+ <=> {1,} \\w letter
    //regex complex("(0|([1-9]\\d+))");
    regex hyperlink("(<a( +)href=\"([^\"]*)\"");
    search_hyperlinks("test.html", hyperlink);
    /*string test = "<a   href   =\"heja1\">here< /><a   href   =\"heja2\">here< />";
    smatch m;
    while (regex_search(test, m, hyperlink)) {
        cout << m.str(m.size() - 1) << endl;
        test = m.suffix().str();
    }*/
    return 0;
}