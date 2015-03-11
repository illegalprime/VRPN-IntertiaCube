#include <jni.h>
#include <iostream>
#include "HelloJNI.h"

using namespace std;

JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv* env, jobject javaThis) {
    cout << "Hello World!" << endl;
}
