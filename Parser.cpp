//
// Created by omer on 19/12/2019.
//

#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include "Parser.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "Print.h"
#include "Sleep.h"
#include "ConditionParser.h"

using namespace std;

Parser::Parser() {
  initVarMap();
}

void Parser::updateMap(list<string> inputFromLexer) {
  list<pair<string,Command*>> cmdList;
  list<pair<string,Command*>> localVarList;

  // Generates list of key-Command
  for(auto it = inputFromLexer.begin(); it != inputFromLexer.end(); ++it) {
    //TODO support local var like: "var h0 = heading"

    if (it->compare("openDataServer") == 0) {
      string port = *(++it);
      cmdList.emplace_back("OpenDataServer", new OpenServerCommand(port));

    } else if ((it->compare("connectControlClient") == 0)) {
      string ip = *(++it);
      string port = *(++it);
      cmdList.emplace_back("connectControlClient", new ConnectCommand(port,ip));

    } else if (it->compare("var") == 0) {
      string name = *(++it);
      string operation = *(++it); // operation such as <-, -> and =
      string value = *(++it);
      if(operation.compare("=") == 0) { // = is for local variables
        localVarList.emplace_back(name, new DefineVarCommand(name, operation, value));
      } else { // -> and <- means server and client can access value
        cmdList.emplace_back(name, new DefineVarCommand(name, operation, value));
      }

    } else if (it->compare("Print") == 0) {
      string name = *it;
      cmdList.emplace_back(name, new Print(*(++it)));

    } else if (it->compare("Sleep") == 0) {
      string name = *it;
      cmdList.emplace_back(name, new Sleep(*(++it)));

    } else if (it->compare("while") == 0) {
      list<pair<string, string>> tokens;
      string type = *it;
      string condition = *(++it);
      while((*(++it)).compare("}") != 0) {
        string name = *it;
        string value = *(++it);
        tokens.emplace_back(name, value);
      }
      //TODO make ConditionParser(string,string,tokens[]) C'tor.
      cmdList.emplace_back(type+condition, new ConditionParser(type,condition,tokens));

    } else if (it->compare("if") == 0) {


    } else {
      auto var = varMap.find(*it);
      //error - var not found in map.
      if(var == varMap.end()) {
        throw "Variable not found/declared: " + (*it);
      }

      ++it;
      try {
        var->second->setValue(stof(*it));
      } catch (const char* e) {
        cerr <<e <<endl;
      }
    }

    //TODO support function commands when done.
  }

  // Generates a map of key-iterator (iterator points to appropriate object)
  for(auto it = cmdList.begin(); it != cmdList.end(); it++) {
    this->cmdMap.emplace(it->first, it);
  }

  for(auto it = localVarList.begin(); it != localVarList.end(); it++) {
    this->localVarMap.emplace(it->first,it);
  }
}

/*void Parser::initVarMap() {
  ifstream inFile;
  string tmp;
  //TODO make sure the path is correct (only when running..)
  inFile.open("../VariablesList.txt");

  // error
  if(!inFile) {
    cerr<<"unable to open file"<<endl;
    return;
  }

  while(inFile >> tmp) {
    this->varMap.emplace(tmp,new Var(tmp, 0));
  }
}*/

