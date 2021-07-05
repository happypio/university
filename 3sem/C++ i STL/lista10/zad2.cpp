#include <iostream>
#include<algorithm>
#include <iterator>
#include <vector>
#include<fstream>
using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int fi(int k) {
    if (k == 1)
        return 1;
    int ans = 0;
    for (int i = 1; i < k; i++) {
        if (gcd(i, k) == 1)
            ans ++;
    }
    return ans;
}

vector<int> tocjent(int k) {
    vector<int> ans;
    for(int i = 1; i <= k; i++) {
        ans.push_back(fi(i));
    }
    return ans;
}

int main() {
    int k;
    cin >> k;
    vector<int> values = tocjent(k);

    ofstream file;
    file.open("phi.txt");
    copy(values.begin(), values.end(), ostream_iterator<int>(file, ";"));
    file.close();
    return 0;
}