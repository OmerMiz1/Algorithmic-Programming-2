//
// Created by omer on 27/12/2019.
//

#include "MainThread.h"
int MainThread::execute() {
  Lexer *lexer = new Lexer();
  Parser *parser = new Parser();

  parser->genMap(lexer->analyzeCode("../fly.txt"));

  this->varList = parser->getVarList();
  this->cmdList = parser->getCmdList();
  this->genMaps();

  // execute commands by order
  while(this->running) {
    for(pair<string,Command*> c : this->cmdList) {
      if(c.first.compare("OpenServerCommand") == 0) {
        c.second->setState(&(this->running));
        thread t1(c.second->execute);
      } else if (c.first.compare("ConnectControlClient")) {
        c.second->setState(&(this->running));
        thread t2(c.second->execute());
      } else {
        c.second->execute();
      }
    }
  }

  return 0;
}

void MainThread::genMaps() {
  list<pair<string,Var*>>::iterator it1;
  list<pair<string,Command*>>::iterator it2;

  // Var map
  for(it1 = this->varList.begin(); it1 != this->varList.end(); ++it1) {
    this->varMap.emplace(it1->first, it1);
  }

  // Commands map
  for(it2 = this->cmdList.begin(); it2 != this->cmdList.end(); ++it1) {
    this->varMap.emplace(it1->first, it1);
  }
}
