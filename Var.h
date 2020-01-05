//
// Created by omer on 20/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__VAR_H_
#define ALGORITHMICPROGRAMMINGPROJECT__VAR_H_

#include <string>
#include <utility>
#include <mutex>

using namespace std;

class Var {
private:
    string name, direction;
    float value;

public:
    Var(string varName, float varValue) : name(move(varName)), value(varValue) {}

    string getName() { return this->name; }

    float getValue() { return this->value; }

    void setValue(float newValue) { this->value = newValue; }
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__VAR_H_
