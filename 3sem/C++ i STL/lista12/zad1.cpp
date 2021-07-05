#include <iostream>
#include <thread>
#include <pthread.h>
#include <time.h>
#include <chrono>

using namespace std;

bool stop = false;

void thread1()
{
    while(!stop)
    {
        cout << "thread1\n";
        int r = rand() % 501 + 500;
        this_thread::sleep_for(chrono::milliseconds(r));
    }
}
void thread2()
{
    while(!stop)
    {
        cout << "thread2\n";
        int r = rand() % 501 + 500;
        this_thread::sleep_for(chrono::milliseconds(r));
    }
}
void thread3()
{
    while(!stop) {
        cout << "thread3\n";
        int r = rand() % 501 + 500;
        this_thread::sleep_for(chrono::milliseconds(r));
    }
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    srand (time(NULL));
    thread t1(&thread1);
    thread t2(&thread2);
    thread t3(&thread3);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    int time = 10;
    while((int)duration.count() <= 60000) {
        if ((int)duration.count() >= time * 1000) {
            cout << time << " seconds" << endl;
            time += 10;
        }
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        this_thread::yield();
    }
    stop = true;
    t1.join();
    t2.join();
    t3.join();
    cout << duration.count() << endl;
    return 0;
}