#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex chargingStation;

void robot(const string& name) {
    for (int i = 0; i < 5; ++i) {
        cout << name << " is checking the charging station..." << endl;

        if (chargingStation.try_lock()) {
            cout << name << " is charging 🚗⚡" << endl;
            this_thread::sleep_for(chrono::milliseconds(300)); // Charging time
            cout << name << " finished charging." << endl;
            chargingStation.unlock();
        } else {
            cout << name << " found station busy. Doing cleaning instead 🧹" << endl;
            this_thread::sleep_for(chrono::milliseconds(200)); // Cleaning time
        }

        this_thread::sleep_for(chrono::milliseconds(100)); // Pause before next attempt
    }
}

int main() {
    thread robot1(robot, "Robot 1");
    thread robot2(robot, "Robot 2");

    robot1.join();
    robot2.join();

    return 0;
}
