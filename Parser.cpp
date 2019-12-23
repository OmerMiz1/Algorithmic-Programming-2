//
// Created by omer on 19/12/2019.

#include "Parser.h"

int updateScopeTokens(list<string>::iterator it, list<string> list);

using namespace std;

void Parser::updateMap(list<string> input) {
  list<pair<string,Command*>> cmdList;
  list<pair<string,Var*>> varList;
  auto it = input.begin();

  // Generates list of key-Command
  while(it != input.end()) {
    if(it->compare("OpenServerCommand") == 0) {
      advance(it,addOpenServerCmd(it, cmdList));
    } else if (it->compare("connectControlClient")==0 ){
      advance(it,addConnectServerCmd(it, cmdList));
    } else if (it->compare("var")==0 ){
      advance(it,addDefineVarCmd(it, cmdList));
    } else if (it->compare("Print")==0 ){
      advance(it, addPrintCmd(it, cmdList));
    } else if (it->compare("Sleep")==0 ){
      advance(it, addSleepCmd(it, cmdList));
    } else if (it->compare("while")==0 || it->compare("if")==0){
      advance(it, addConditionCmd(it, cmdList));
    } else {
      advance(it, addAssignment(it, cmdList));
    }
    //TODO support FunctionCommands when done.
  }

  // Add Commands to their map.
  for(auto it = cmdList.begin(); it != cmdList.end(); it++) {
    this->cmdMap.emplace(it->first, it);
  }
  // Add Vars to their map.
  for(auto it = varList.begin(); it != varList.end(); it++) {
    this->varMap.emplace(it->first, it);
  }
}

unordered_map<string, list<pair<string,Command*>>::iterator> Parser::getCmdMap() {
  return this->cmdMap;
}

unordered_map<string,list<pair<string,Var*>>::iterator> Parser::getVarMap() {
  return this->varMap;
}

int Parser::addOpenServerCmd(list<string>::iterator it, list<pair<string,Command*>> list) {
  ++it;
  string port = *it;
  list.emplace_back("OpenDataServer", new OpenServerCommand(port));
  return 2;
}

int Parser::addConnectServerCmd(list<string>::iterator it, list<pair<string,Command*>> list) {
  ++it;
  string ip = *it;
  ++it;
  string port = *it;
  // string.c_str returns the string as const char*.
  list.emplace_back("connectControlClient", new ConnectCommand(port.c_str(),ip.c_str()));
  return 3;
}

int Parser::addDefineVarCmd(list<string>::iterator it,list<pair<string,Command*>> cmds) {
  ++it;
  string name = *it;
  ++it;
  string operation = *it; // operation such as <-, -> and =
  ++it;
  string value = *it;
  cmds.emplace_back(name, new DefineVarCommand(name, operation, value));
  return 4;
  /*if(operation.compare("=") == 0) { // = is for local variables
    localVarList.emplace_back(name, new DefineVarCommand(name, operation, value));
  } else { // -> and <- means server and client can access value
    cmdList.emplace_back(name, new DefineVarCommand(name, operation, value));
  }*/
}

int Parser::addPrintCmd(list<string>::iterator it, list<pair<string, Command *>> list) {
  string name = *it;
  ++it;
  list.emplace_back(name, new Print(*it));
  return 2;
}

int Parser::addSleepCmd(list<string>::iterator it, list<pair<string, Command *>> list) {
  string name = *it;
  ++it;
  list.emplace_back(name, new Sleep(*it));
  return 2;
}

int Parser::addConditionCmd(list<string>::iterator it, list<pair<string, Command *>> list) {
  std::list<string> innerScopeTokens;
  ConditionCommand* cmd;
  Parser* parser = new Parser();
  string myKey, myType = (*it);
  int tokensCount = 0, conditionCount;

  // advance from "while" or "if" token to condition.
  ++it;
  ++tokensCount;

  // NOTE: *it == "my_condition" i.e "alt < 1000"
  if(myType.compare("while") == 0) {
    cmd = new LoopCommand(*it);
    ++(this->loopCount);
    conditionCount = this->loopCount;
  } else {
    cmd=new IfCommand(*it);
    ++(this->ifCount);
    conditionCount = this->ifCount;
  }

  // By adding the while #<num> it's possible to distinguish between diff loops.
  myKey = (*it) + " #" + to_string(conditionCount);

  // Proceed to loop's body tokens (required for updateScopeToken())
  ++it;
  ++tokensCount;

  // Insert entire scope (tokens) into a list. Then let local parser parse it.
  tokensCount += updateScopeTokens(it, innerScopeTokens);
  parser->updateMap(innerScopeTokens);

  // Initialize command with condition, then inject the local parser's results.
  cmd->setCommandMap(parser->getCmdMap());
  cmd->setVarMap(parser->getVarMap());
  //TODO support global vars/cmds

  list.emplace_back(myKey, cmd);
  return tokensCount;
}

int Parser::addAssignment(list<string>::iterator it, list<pair<string, Command *>> list) {
  int tokensCount = 0;

  //TODO after enabling global variables, make corrections here to support.
  //If the var is not recognized withing this scope throw an error.
  if (this->cmdMap.find(*it) != this->cmdMap.end()) {
    throw "Invalid assignment command: no such Var \"" + (*it);
  }

  //TODO continue working on parser from here!


  return tokensCount;
}

/**
 *
 * @param it points to the condition token (1 token after the type token)
 * @param list to update with current scopes tokens.
 * @return a counter to how many tokens has been read, to advance iterator.
 */
int updateScopeTokens(list<string>::iterator it, list<string> list) {
  int count = 0;

  // NOTE: no nested scopes.
  for(count=0; it->compare("}") != 0; ++it, ++count) {
    list.emplace_back(*it);
  }
  return count;
}

/*int getParseType(string str) {
  if(str.compare("OpenServerCommand") == 0) {
    return 1;
  } else if (str.compare("connectControlClient")==0 ){
    return 2;
  } else if (str.compare("var")==0 ){
    return 3;
  } else if (str.compare("Print")==0 ){
    return 4;
  } else if (str.compare("Sleep")==0 ){
    return 5;
  } else if (str.compare("while")==0 ){
    return 6;
  } else if (str.compare("if")==0 ){
    return 7;
  } else {
    return 8;
  }
}*/