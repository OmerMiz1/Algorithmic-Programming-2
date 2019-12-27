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
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "Print.h"
#include "Sleep.h"
#include "ConditionCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"

/*הפרסר בעיקרון מה שהוא עושה זה מחזיר מערך של קומנדים, החלטנו שהוא מסתיים כשהמערך גמור ריק. נעשה זאת רקורסיבית
 * בתו הבנאי של התנאים נאמר לו שהוא מקבל מצביע למערך גם כן והוא מסיים כשהוא רואה סוגריים מסולסלים. מה קורה? הוא בעצמו בונה מערך של קומנדים
 * שמכיל את כל מה שבתוך הסוגריים המסולסלים.*/

using namespace std;

class Parser {
 private:
  int loopCount = 0, ifCount = 0;
  list<pair<string, Var*>> varList;
  list<pair<string, Command*>> cmdList;

  int addOpenServerCmd(list<string>::iterator it);
  int addConnectServerCmd(list<string>::iterator it);
  int addDefineVarCmd(list<string>::iterator it);
  int addPrintCmd(list<string>::iterator it);
  int addSleepCmd(list<string>::iterator it);
  int addConditionCmd(list<string>::iterator it);
  int addAssignment(list<string>::iterator it);

 public:
  ~Parser();
  void genMap(list<string> input);
  list<pair<string, Var*>> getVarList();
  list<pair<string, Command*>> getCmdList();

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
