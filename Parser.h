//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
#define ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_

#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class Parser {
 private:
  list<string> varList;
 public:
  void genMap(list<string> inputFromLexer);
  void initVarList();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
