#include <iostream>
#include<exception>
#include<iterator>
#include<fstream>
#include<algorithm>
using namespace std;

void count_letters(string name) {
    int letters[26]{};
    int sum = 0;
    ifstream file (name);
    for_each(istreambuf_iterator<char>(file) , istreambuf_iterator<char>(), [&](char c){
        if ('A' <= c && c <= 'Z') {
            letters[(int)(c) - 65] ++;
            sum ++;
        }
        if ('a' <= c && c <= 'z') {
            letters[(int)(c) - 97] ++;
            sum ++;
        }
    });
    file.close();
    //double check = 0;
    for (int i = 0; i < 26; i++) {
        cout << (char) (i + 65) << " occured " << letters[i] << " times, avg: " << letters[i] / (double) sum<< endl;
        //check += letters[i] / (double) sum;
    }
    //cout << check << endl;
}

int main(int argc, char *argv[])
{
    try{
        if (argc < 2)
            throw "Exception: to few arguments!\n";
        string name = argv[1];
        count_letters(name);
    }
    catch(char const* e) {
        cout << e;
    }
    return 0;
}