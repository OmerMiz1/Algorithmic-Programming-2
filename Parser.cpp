//
// Created by omer on 19/12/2019.

#include "Parser.h"

using namespace std;

/**
 * @param map includes all possible command objects.
 */
Parser::Parser(unordered_map<string, Command *> *map) : cmdMap(map) {}

Parser::~Parser() {
    this->cmdMap->clear();
}

/** Calls the command execution's function.
 *
 * @param it points to current token cmd. If name isnt recognized by map, its
 * an assignment command which will be treated using DefineVarCommand
 * @return How many tokens to jump to get to next command.
 */
int Parser::parseCommand(list<string>::iterator it) {
    unordered_map<string, Command *>::iterator currCmd = this->cmdMap->find(*it);

    // Cmd found in map, just executes
    if (currCmd != this->cmdMap->end()) {
        return currCmd->second->execute(it);

        // Cmd not in map so it is an assignment.
    } else {
        return this->cmdMap->find("var")->second->execute(it);
    }
    //TODO support FunctionCommands when done.
}

/**
 *
 * @param path to the xml file.
 * @return Map<VAR_NAME, INDEX_BY_XML>. With that map OpenServerCommand can find
 * the appropriate value for specific variable, read from simulator.
 */
unordered_map<string, int> Parser::parseXml(const char *path) {
    smatch match;
    string str;
    ifstream file(path);
    unordered_map<string, int> symTable;

    /* Regex find lines starting with <name> and ending with </name> from xml and
       keeps w/e is between them.*/
    regex varPathRx("\\s*<name>(.*)<\\/name>");

    // Iterates each line in XML, index each path accordingly.
    for (int index = 0; getline(file, str);) {
        if (regex_search(str, match, varPathRx)) {
            symTable.emplace(match[1], index);
            index++;
        }
    }

    file.close();
    return symTable;
}

/**
 *
 * @param OpenServerCommand sends the incoming string. String looks like:
 * {0.0,32.4,33.1,....} and should have 36 or so floats.
 * @return Map<INDEX, VALUE> with updated values from serer.
 */
unordered_map<int, float>* Parser::parseServerOutput(string incoming) {
    unordered_map<int, float>* result = new unordered_map<int,float>;
    smatch rxMatch;

    // Regex find all floats the brackets.
    regex floatsRx("(\\d+\\.\\d+)");
    regex_search(incoming, rxMatch, floatsRx);
    int index = 0;

    // Index each float value.
    for (string match : rxMatch) {
        // If a value is corrupt (includes non decimal chars) return error value
        if(match.find_first_not_of("0123456789.") != string::npos) {
            return nullptr;
        }
        //TODO findout why buffer is too large
        result->emplace(index, stof(match));
        index++;
    }
    return result;
}

/**
 *
 * @param it points to the condition token (1 token after the type token)
 * @param list to update with current scopes tokens.
 * @return a counter to how many tokens has been read, to advance iterator.
 */
//TODO should be used in ConditionCommand when parsing scope
int updateScopeTokens(list<string>::iterator it, list<string> list) {
    int count = 0;

    // NOTE: no nested scopes.
    for (count = 0; it->compare("}") != 0; ++it, ++count) {
        list.emplace_back(*it);
    }
    return count;
}

/*list<pair<string, Command*>> Parser::getCmdList() {
  return this->cmdList;
}

list<pair<string, Var*>> Parser::getVarList() {
  return this->varList;
}*/

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

/*
int Parser::addPrintCmd(list<string>::iterator it) {
  string name = *it;
  ++it;
  this->cmdList.emplace_back(name, new Print(*it));
  return 2;
}*/

/*int Parser::addSleepCmd(list<string>::iterator it) {
  string name = *it;
  ++it;
  this->cmdList.emplace_back(name, new Sleep(*it));
  return 2;
}*/

/*int Parser::addConnectServerCmd(list<string>::iterator it) {
  ++it;
  string ip = *it;
  ++it;
  string port = *it;
  // string.c_str returns the string as const char*.
  this->cmdList.emplace_back("connectControlClient",
      new ConnectCommand(port.c_str(),ip.c_str()));
  return 3;
}

int Parser::addDefineVarCmd(list<string>::iterator it) {
  Command* cmd;
  ++it; // "var" advance to "<var_name>"
  string name = *it;
  ++it; // "<var_name> advance to "<operation_type>", {"<-", "->", "="}
  string operation = *it;
  ++it; // "<operation_type>" advance to "<var_value>" {value \ another var}
  string value = *it;

  if(operation.compare("->") == 0) {

  } else if (operation.compare("<-") == 0) {

  } else if (operation.compare("=") == 0) {

  } else {
    //TODO this line is only for debugging, remove before done
    throw "ERROR in add defineVarCommand with:" + name + " " + operation + " " + value;
  }

  this->cmdList.emplace_back(name, new DefineVarCommand(name, operation, value));
  return 4; // next command token is 4 tokens ahead.
}

int Parser::addConditionCmd(list<string>::iterator it) {
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
  tokensCount += countScopeTokens(it, innerScopeTokens);
  parser->parseCommand(innerScopeTokens);

  // Initialize command with condition, then inject the local parser's results.
  cmd->setCommandMap(parser->getCmdList());
  cmd->setVarMap(parser->getVarList());
  //TODO support global vars/cmds

  this->cmdList.emplace_back(myKey, cmd);
  return tokensCount;
}

int Parser::addAssignment(list<string>::iterator it) {
  int tokensCount = 0;

  //TODO after enabling global variables, make corrections here to support.
  //If the var is not recognized withing this scope throw an error.
  if (this->cmdMap.find(*it) != this->cmdMap.end()) {
    throw "Invalid assignment: Var not found withing scope \"" + (*it);
  }


  //TODO continue working on parser from here!
  return tokensCount;
}*/
