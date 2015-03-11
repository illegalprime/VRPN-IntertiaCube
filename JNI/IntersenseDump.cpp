#include <jni.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "IntersenseDump.h"

using namespace std;

JNIEXPORT void JNICALL Java_IntersenseDump_addRotListener (JNIEnv *, jobject, jobject)
;

void runJavaRotCallback(double x, double y, double z, double theta);

JNIEXPORT void JNICALL Java_IntersenseDump_addRotListener (JNIEnv* env, jobject jThis, jobject jListener) {
    // Get an object's class
    jclass listenerClass = env->GetObjectClass(jListener);
    // Get callback method ID
    jmethodID rotCallback = env->GetMethodID(listenerClass, "onRotationalChange", "(DDDD)V");
    // Check if found
    if (rotCallback == NULL) {
        cout << "Could not find function" << endl;
        return;
    }

    chrono::milliseconds duration(1000);
    this_thread::sleep_for(duration);

    // Call the method!
    env->CallVoidMethod(jListener, rotCallback, 0.0, 0.0, 0.0, 0.0);
}


void runJavaRotCallback(double x, double y, double z, double theta) {

}
