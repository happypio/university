#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    cout << "Wprowadź napis: " << endl;
    string s;
    cin >> s;
    string old_s = s;
    cout << endl << s << endl;
    next_permutation(s.begin(), s.end());
    while(old_s != s) {
        cout << s << endl;
        next_permutation(s.begin(), s.end());
    }

}