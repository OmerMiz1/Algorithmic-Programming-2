//
// Created by omer on 27/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_
#define ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_

#include <string>
#include <list>
#include <unordered_map>
#include <thread>

#include "Command.h"
#include "Var.h"
#include "Parser.h"
#include "Lexer.h"

class MainThread : Command {
 private:
  bool running = true;
  unordered_map<string, list<pair<string,Var*>>::iterator> varMap;
  list<pair<string, Var*>> varList;

  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;
  list<pair<string, Command*>> cmdList;

 public:
  ~MainThread();
  int execute() override;
  void genMaps();

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_
