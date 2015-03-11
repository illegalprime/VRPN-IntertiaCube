#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

void printLater(char const* message) {
    chrono::milliseconds oneSecond(1000);
    this_thread::sleep_for(oneSecond);

    cout << message << endl;
}

int main(int argc, char** argv) {
    thread fork(printLater, "This message will come later.");
    cout <<                 "This message will come first." << endl;
    fork.join();
    return 0;
}
