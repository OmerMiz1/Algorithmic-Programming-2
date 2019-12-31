//
// Created by omer on 30/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__PROGRAMSTATE_H_
#define ALGORITHMICPROGRAMMINGPROJECT__PROGRAMSTATE_H_

class ProgramState {
    bool isRunning = true;

public:
    bool getState() { return isRunning; }

    void turnOff() { this->isRunning = false; }

    void turnOn() { this->isRunning = true; }
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PROGRAMSTATE_H_
