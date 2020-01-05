#include <iostream>
#include "MainThread.h"

int main(int argc, char* argv[]) {
    if(argc <= 0) {
        throw "No arguments for file path";
    }

    // Main thread is in charge program flow.
    MainThread *main = new MainThread(argv[1]);
    try {
        main->execute();
    } catch (const char *e) {
        cout << e << endl;
    }

    delete main;
    return 0;
}
