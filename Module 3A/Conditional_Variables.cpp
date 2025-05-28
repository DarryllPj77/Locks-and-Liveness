#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void worker() {
    this_thread::sleep_for(chrono::seconds(2)); // Simulate some work
    {
        lock_guard<mutex> lock(mtx); // Lock the mutex to safely update 'ready'
        ready = true;
        cout << "Worker: work is done, notifying main thread..." << endl;
    }
    cv.notify_one(); // Notify the main thread that work is done
}

int main() {
    thread t(worker); // Start the worker thread

    unique_lock<mutex> lock(mtx); // Lock the mutex to wait safely
    cout << "Main: waiting for the worker to finish..." << endl;
    cv.wait(lock, []{ return ready; }); // Wait until 'ready' becomes true

    cout << "Main: received notification. Proceeding..." << endl;

    t.join(); // Wait for the worker thread to finish
    return 0;
}

