#include <iostream>
#include <random> 
#include <chrono>
#include <cmath>
#include <fstream>

#include <numeric>
using namespace std;

static default_random_engine dre;

char random_letter() {
    double s = 0;
    double data[]{8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03, 5.92, 7.31,
    0.10, 0.69, 3.98, 2.61, 6.95, 7.68, 1.82, 0.11, 6.02, 6.28, 9.10,
    2.88, 1.11, 2.09, 0.17, 2.11, 0.07}; //probabilitys (%) of each letter (from a-z)
    
    //check if data are correct
    //cout << accumulate(data, data + 26, s) << endl << sizeof(data)/sizeof(data[0]) << endl;

    double letters[26]; //range of each letter
    for (int i = 0; i < 26; i ++) {
        s += data[i];
        letters[i] = s;
    } 

    uniform_real_distribution<double> distribution(0.0, 99.99);
    double r = distribution(dre);

    double bef = 0;
    for (int i = 0; i < 26; i++) {
        if (bef <= r && r < letters[i])
            return (char) (i + 'a');
        bef = letters[i];
    }
    throw "Exception: Wrong data!\n";

}

void generate(int l, string name) {
    binomial_distribution<int> bin_distribution(11, 0.5);
    ofstream file;
    file.open(name);
    for (int i = 0; i < l; i ++) {
        int sen_length = 1 + bin_distribution(dre);
        string sen = "";
        for (int j = 0; j < sen_length; j++) {
            char c = random_letter();
            sen += c;
        } 
        file << sen << " ";
    }
    file.close();
}

int main(int argc, char *argv[])
{
    dre.seed(chrono::system_clock::now().time_since_epoch().count());
    try{
        if (argc < 3)
            throw "Exception: to few arguments!\n";
        string l = argv[1];
        int length = 0;
        int d = 0;
        for (int i = l.size() - 1; i >= 0; i--) {
            length += pow (10, d) * ((int) l[i] - '0');
            d ++;
        }
        string file_name = argv[2];
        generate(length, file_name);
    }
    catch(char const* e) {
        cout << e;
    }
    return 0;
}