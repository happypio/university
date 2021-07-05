#include<iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        fs::path path(argv[1]);
        if (fs::exists(argv[1])) {
            if (fs::is_directory(argv[1]))
            {
                for (auto p: fs::directory_iterator(argv[1])) {
                    cout << (p.path()) << endl;
                }
            }   
            else {
                cout << argv[1] << " is not directory!" << endl;
            }
        }
        else
        {
            cout << argv[1] << " does not exist!" << endl;
        }
    }
    return 0;
}
//compile g++ -std=c++17 zad4.cpp -o zad4