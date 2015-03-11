#include <iostream>
#include <stdio.h>
#include <vrpn_Tracker.h>

using namespace std;

int i = 0;

void VRPN_CALLBACK handleGyroChange(void* userData, const vrpn_TRACKERCB t);

int main(int argc, char** argv) {
    char const* deviceName = "Tracker0@localhost";
    printf("Attempting to attach to device: %s\n", deviceName);
    vrpn_Tracker_Remote gyroTrack(deviceName);
    gyroTrack.register_change_handler(&i, handleGyroChange);

    while (true) {
        gyroTrack.mainloop();
    }
    return 0;
}

void VRPN_CALLBACK handleGyroChange(void* userData, const vrpn_TRACKERCB t) {
    cout << "i equals " << ++(*(int*)userData) << "\t";
    printf("Tracker %d is now at position ( %g, %g, %g ) and orientation [ %g, %g, %g, %g ]\n",
            t.sensor, t.quat[0], t.quat[1], t.quat[2], t.quat[3],
            t.pos[0], t.pos[1], t.pos[2]);
}
