#include <iostream>
#include <thread>
//#include <pthread.h>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    int time = 0;
    while((int) duration.count() < 10000) {
        if ((int) duration.count() >= 5000 && time == 0) {
            time++;
            cout << "5 seconds left" << endl;
        }
        if ((int) duration.count() >= 7000 && time == 1) {
            time++;
            cout << "3 seconds left" << endl;
        }
        if ((int) duration.count() >= 9000 && time == 2) {
            time++;
            cout << "1 seconds left" << endl;
        }
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        this_thread::yield();
    }
    cout << "It took: " << duration.count() << " milliseconds" << endl;
    return 0;
}