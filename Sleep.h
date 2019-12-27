//
// Created by omer on 21/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__SLEEP_H_
#define ALGORITHMICPROGRAMMINGPROJECT__SLEEP_H_

#include <zconf.h>
#include <chrono>
#include <string>
#include <iostream>
#include <thread>
#include "Command.h"

using namespace std;

class Sleep : public Command {
 private:
  int d;

 public:
  int execute(list<string>::iterator it) override {
    ++it;
    try {
      chrono::milliseconds duration(stoi(*it));
      this_thread::sleep_for(duration);
    } catch (const char* e) {
      cerr<<e<<endl;
    }
    return 2;
  }
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__SLEEP_H_
