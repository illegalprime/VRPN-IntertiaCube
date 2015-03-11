#include "vrpn_Analog.h"

#include <iostream>
using namespace std;

void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a) {
    int channels = a.num_channel;
    cout << "Coords: ";
    for (int i = 0; i < channels; ++i) {
        cout << a.channel[i] << "\t";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    vrpn_Analog_Remote* vrpnAnalog = new vrpn_Analog_Remote("Mouse0@localhost");

    vrpnAnalog->register_change_handler(0, handle_analog);

    while (true) {
        vrpnAnalog->mainloop();
    }
    return 0;
}
