//
// Created by omer on 20/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__VAR_H_
#define ALGORITHMICPROGRAMMINGPROJECT__VAR_H_

#include <string>
#include <utility>
using namespace std;

class Var {
 private:
  string name;
  float value;
  //TODO add string that indicates the var location in sim

 public:
  Var(string varName, float varValue) : name(move(varName)), value(varValue) {}
  string getName() {return this->name;}
  float getValue() {return this->value;}
  void setValue(float newValue) {this->value = newValue;}
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__VAR_H_
