//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
#define ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_

#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include "Command.h"
#include "Var.h"
#include "Parser.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "Print.h"
#include "Sleep.h"
#include "ConditionParser.h"
#include "LoopCommand.h"

using namespace std;

class Parser {
 private:
  unordered_map<string, Var*> varMap;
  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;

 public:
  ~Parser() = default;
  void updateMap(list<string> input);
  unordered_map<string, list<pair<string,Command*>>::iterator> getCmdMap() { return this->cmdMap;}
  unordered_map<string, Var*> getVarMap() {return this->varMap;}

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
