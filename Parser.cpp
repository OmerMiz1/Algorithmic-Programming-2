//
// Created by omer on 19/12/2019.
//


#include "Parser.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "Print.h"
#include "Sleep.h"
#include "ConditionCommand.h"
#include "LoopCommand.h"
#include "ConditionCommand.h"

using namespace std;

/*int getParseType(string);*/
int addOpenServerCmd(list<string>::iterator,list<pair<string,Command*>>);
int addConnectServerCmd(list<string>::iterator,list<pair<string,Command*>>);
int addDefineVarCmd(list<string>::iterator,list<pair<string,Command*>>);
int addPrintCmd(list<string>::iterator,list<pair<string,Command*>>);
int addSleepCmd(list<string>::iterator,list<pair<string,Command*>>);
int addWhileCmd(list<string>::iterator,list<pair<string,Command*>>);
int updateScopeTokens(list<string>::iterator, list<string>);


void Parser::updateMap(list<string> input) {
  list<pair<string,Command*>> cmdList;
  list<pair<string,Command*>> varList;
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
    } else if (it->compare("while")==0 ){
      advance(it, addWhileCmd(it, cmdList));
    } else if (it->compare("if")==0 ){
      advance(it, addIfCmd(it,cmdList));
    } else {
      advance(it, addOther(it,cmdList));
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

int addOpenServerCmd(list<string>::iterator it, list<pair<string,Command*>> list) {
  ++it;
  string port = *it;
  list.emplace_back("OpenDataServer", new OpenServerCommand(port));
  return 2;
}

int addConnectServerCmd(list<string>::iterator it, list<pair<string,Command*>> list) {
  ++it;
  string ip = *it;
  ++it;
  string port = *it;
  // string.c_str returns the string as const char*.
  list.emplace_back("connectControlClient", new ConnectCommand(port.c_str(),ip.c_str()));
  return 3;
}

int addDefineVarCmd(list<string>::iterator it,list<pair<string,Command*>> cmds) {
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

int addPrintCmd(list<string>::iterator it, list<pair<string, Command *>> list) {
  string name = *it;
  ++it;
  list.emplace_back(name, new Print(*it));
  return 2;
}

int addSleepCmd(list<string>::iterator it, list<pair<string, Command *>> list) {
  string name = *it;
  ++it;
  list.emplace_back(name, new Sleep(*it));
  return 2;
}

int addWhileCmd(list<string>::iterator it, list<pair<string, Command *>> list) {
  std::list<string> innerScopeTokens;
  string closeScopeToken("}");
  Parser* parser = new Parser();
  int tokensCount = 0;

  ++it;
  ++tokensCount;
  string conditionVal(*it);
  ++it;
  ++tokensCount;

  // insert entire scope (tokens) into a list.
  tokensCount += updateScopeTokens(it, innerScopeTokens);
  // parse tokens into a command map (with a difference parser object!).
  parser->updateMap(innerScopeTokens);
  ConditionCommand* cmd = new LoopCommand(conditionVal, parser);

  //TODO not sure about this cast here. supposed to be fine.
  list.emplace_back("while", cmd);
  return tokensCount;
}

int addIfCmd(list<string>::iterator it, list<pair<string, Command *>> list) {

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