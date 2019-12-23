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
#include "ConditionCommand.h"
#include "LoopCommand.h"
/*הפרסר בעיקרון מה שהוא עושה זה מחזיר מערך של קומנדים, החלטנו שהוא מסתיים כשהמערך גמור ריק. נעשה זאת רקורסיבית
 * בתו הבנאי של התנאים נאמר לו שהוא מקבל מצביע למערך גם כן והוא מסיים כשהוא רואה סוגריים מסולסלים. מה קורה? הוא בעצמו בונה מערך של קומנדים
 * שמכיל את כל מה שבתוך הסוגריים המסולסלים.*/

using namespace std;

class Parser {
 private:
  unordered_map<string, list<pair<string,Var*>> varMap;
  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;

 public:
  ~Parser() = default;
  void updateMap(list<string> input);
  unordered_map<string, list<pair<string,Command*>>::iterator> getCmdMap() { return this->cmdMap;}
  unordered_map<string, Var*> getVarMap() {return this->varMap;}

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
