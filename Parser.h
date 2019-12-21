//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
#define ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_

#include <string>
#include <list>
#include <unordered_map>
#include "Command.h"
#include "Var.h"

using namespace std;

class Parser {
 private:
  unordered_map<string, Var*> varMap;
  unordered_map<string, list<pair<string,Command*>>::iterator> localVarMap;
  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;

 public:
  Parser();
  ~Parser() = default;
  void updateMap(list<string> inputFromLexer);

  /*void initVarMap();*/
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
