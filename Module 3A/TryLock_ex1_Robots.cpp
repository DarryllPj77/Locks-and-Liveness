#include <iostream>                // Includes input-output stream for cout
#include <thread>                 // Includes threading support
#include <mutex>                  // Includes mutex and try_lock
#include <chrono>                 // Includes time utilities like sleep_for

using namespace std;              // Avoids having to write std:: before common objects

mutex chargingStation;            // Shared mutex representing the charging station

// ------------------------- Robot Function -------------------------
void robot(const string& name) {  // Function for each robot thread; takes the robot's name
    for (int i = 0; i < 5; ++i) { // Repeat 5 times: simulates multiple tasks over time
        cout << name << " is checking the charging station..." << endl;

        if (chargingStation.try_lock()) {   // Try to lock the mutex without blocking
            cout << name << " is charging 🚗⚡" << endl;

            // Simulate charging by sleeping for 300 milliseconds
            this_thread::sleep_for(chrono::milliseconds(300));

            cout << name << " finished charging." << endl;

            chargingStation.unlock(); // Release the lock so others can use the station
        } else {
            // If the lock couldn't be acquired, do something else
            cout << name << " found station busy. Doing cleaning instead 🧹" << endl;

            // Simulate alternate work (e.g., cleaning)
            this_thread::sleep_for(chrono::milliseconds(200));
        }

        // Pause between attempts to check the station
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
// ------------------------- Main Function -------------------------
int main() {
    // Create two threads running the robot function with different names
    thread robot1(robot, "Robot 1");
    thread robot2(robot, "Robot 2");

    // Wait for both threads to finish
    robot1.join();
    robot2.join();

    return 0; // End of program
}
