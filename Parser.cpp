//
// Created by omer on 19/12/2019.
//

#include <unordered_map>
#include <functional>
#include "Parser.h"
#include "Command.h"
#include "OpenServerCommand.h"

void Parser::genMap(list<string> input) {
  unordered_map<string, Command> commandMap;
  list<string>::iterator it;

  for(it = input.begin(); it != input.end(); /*ןsome increment*/ ) {
    if ((*it).compare("OpenDataServer") == 0) {

    }


  }
}
