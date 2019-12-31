#include <iostream>
#include "MainThread.h"

int main() {
    MainThread *main = new MainThread();
    try {
        main->execute();
    } catch (const char *e) {
        cout << e << endl;
    }


    return 0;
}
