#ifndef ASYNC_REMOTE_TRACKER
#define ASYNC_REMOTE_TRACKER

#include <jni.h>
#include <functional>
#include <thread>
#include <atomic>

class AsyncRemoteTracker {
    public:
        AsyncRemoteTracker(char const* trackerID);
        ~AsyncRemoteTracker();
        bool setOnRotateListener(JNIEnv* env, jobject jThis, jobject jListener);
        void clearRotateListener();
        void enable();
        void disable();
    private:
        std::atomic<bool> isEnabled;
        vrpn_Remote_Tracker tracker;
        std::function<void(double, double, double, double)> rotateCallback;
        std::thread* listener;

        void VRPN_CALLBACK handleGyroChange(void* userData, const vrpn_TRACKERCB t);
        void mainloop();
}

#endif
