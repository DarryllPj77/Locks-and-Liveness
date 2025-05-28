#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx1;
mutex mtx2;

void task1() {
    lock_guard<mutex> lock1(mtx1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    cout << "Task 1 locked mtx1, trying to lock mtx2..." << endl;

    lock_guard<mutex> lock2(mtx2); // Deadlock happens here if task2 holds mtx2
    cout << "Task 1 acquired both locks." << endl;
}

void task2() {
    lock_guard<mutex> lock2(mtx2);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    cout << "Task 2 locked mtx2, trying to lock mtx1..." << endl;

    lock_guard<mutex> lock1(mtx1); // Deadlock happens here if task1 holds mtx1
    cout << "Task 2 acquired both locks." << endl;
}

int main() {
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
