// #include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vrpn_Tracker.h>

using namespace std;

void VRPN_CALLBACK handleGyroChange(void* userData, const vrpn_TRACKERCB t);

void asyncTrackerUpdate(vrpn_Tracker_Remote* tracker) {
    while (true) {
        tracker->mainloop();
    }
}

int main(int argc, char** argv) {
    char const* deviceName = "Tracker0@localhost";
    printf("Attempting to attach to device: %s\n", deviceName);
    vrpn_Tracker_Remote gyroTrack(deviceName);
    gyroTrack.register_change_handler(NULL, handleGyroChange);
    thread updater(asyncTrackerUpdate, &gyroTrack);

    chrono::milliseconds oneSecond(1000);
    for (int i = 0; i < 10; ++i) {
        cout << "Timeout in " << i << " seconds..." << endl;
        this_thread::sleep_for(oneSecond);
    }
    updater.join();
    return 0;
}

void VRPN_CALLBACK handleGyroChange(void* userData, const vrpn_TRACKERCB t) {
    printf("Tracker %d is now at position ( %g, %g, %g ) and orientation [ %g, %g, %g, %g ]\n",
            t.sensor, t.quat[0], t.quat[1], t.quat[2], t.quat[3],
            t.pos[0], t.pos[1], t.pos[2]);
}

