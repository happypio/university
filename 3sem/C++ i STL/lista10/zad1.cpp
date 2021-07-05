#include <iostream>
#include<algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main() {
    vector<double> values(istream_iterator<double>(cin), 
                   istream_iterator<double>{});
    for_each(values.begin(), values.end(), [](double n){cout << n << " ";});
    cout << endl;
    return 0;
}