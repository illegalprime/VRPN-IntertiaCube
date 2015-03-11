#include "AsyncRemoteTracker.hpp"

AsyncRemoteTracker::AsyncRemoteTracker(char const* trackerID)
    : tracker(trackerID)
{
    isEnabled = false;
    rotateCallback = NULL;
}

bool AsyncRemoteTracker::setOnRotateListener(JNIEnv* env, jobject jThis, jobject jListener) {
        // Get an object's class
        jclass listenerClass = env->GetObjectClass(jListener);
        // Get callback method ID
        jmethodID rotCallback = env->GetMethodID(listenerClass, "onRotationalChange", "(DDDD)V");
        // Check if found
        if (rotCallback == NULL) {
            cout << "Could not find function!" << endl;
                 << "Maybe you didn't pass a VrpnTracker.RotListener class." << endl;
            return false;
        }
        // Save the method
        this.rotateCallback = [=](double x, double y, double z, double theta) {
            env->CallVoidMethod(jListener, rotCallback, x, y, z, theta);
        };
        // Attatch method to the listener
        tracker.register_change_handler(NULL, handleGyroChange);
        return true;
}

void VRPN_CALLBACK AsyncRemoteTracker::handleGyroChange(void* userData, const vrpn_TRACKERCB t) {
    if (this.rotateCallback != NULL) {
        this.rotateCallback(t.quat[0], t.quat[1], t.quat[2], t.quat[3]);
    }
}

void AsyncRemoteTracker::enable() {
    isEnabled = true;
    listener = new std::thread(mainloop);
}

void AsyncRemoteTracker::disable() {
    isEnabled = false;
    listener->join();
    delete listener;
}

void AsyncRemoteTracker::mainloop() {
    while (isEnabled) {
        tracker.mainloop();
    }
}
