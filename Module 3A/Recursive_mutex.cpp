#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

recursive_mutex rmtx;

void functionB() {
    rmtx.lock();
    cout << "functionB: lock acquired" << endl;
    rmtx.unlock();
}

void functionA() {
    rmtx.lock();
    cout << "functionA: lock acquired" << endl;

    // Call another function that also locks the same mutex
    functionB();

    rmtx.unlock();
}

int main() {
    thread t(functionA);
    t.join();
    return 0;
}
