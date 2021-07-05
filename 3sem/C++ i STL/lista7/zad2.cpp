#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

static default_random_engine dre;

void uniform_dsb() {
    // equally probable random numbers in [0.0, 1.0)
    uniform_real_distribution<double> distribution(0.0, 1.0);
    map <double, int> count;
    for (int i = 0; i < 1000; i ++)
        count[distribution(dre)] ++;
    ofstream file;
    file.open("unfiorm.csv");
    for (auto x : count)
        file << x.first << "," << x.second << endl;
    file.close();

}

void binomal_dsb() {
    // binomial distribution in [0, 9]
    binomial_distribution<int> distribution(9, 0.5);
    map <int, int> count;
    for (int i = 0; i < 1000; i ++)
        count[distribution(dre)] ++;
    ofstream file;
    file.open("binomial.csv");
    for (auto x : count)
        file << x.first << "," << x.second << endl;
    file.close();
}

void normal_dsb() {
    //normal distribution with mean 5.0, standard deviation 2.0
    normal_distribution<double> distribution{0.0, 1.0};
    map <int, int> count; // numbers of elements in [floor(x), ceiling(x) )
    for (int i = 0; i < 1000; i ++)
    {
        int tmp = floor(distribution(dre));
        //tmp is actually sumbol of range [floor(x), ceiling(x)]
        count[tmp] ++;
    }
    ofstream file;
    file.open("normal.csv");
    for (auto x : count)
        file << x.first << "," << x.second << endl;
    file.close(); 
}  

int main() {

    dre.seed(chrono::system_clock::now().time_since_epoch().count());
    uniform_dsb();
    binomal_dsb();
    normal_dsb();
    return 0;
}