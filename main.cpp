#include <iostream>
#include "MainThread.h"

int main(int argc, char* argv[]) {
    // Main thread is in charge program flow.
    MainThread *main = new MainThread(argv[1]);
    try {
        main->execute();
    } catch (const char *e) {
        cout << e << endl;
    }
    return 0;
}
