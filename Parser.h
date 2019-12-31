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
#include <regex>

#include "Command.h"
#include "SymbolTable.h"


using namespace std;

class Parser {
private:
    unordered_map<string, Command *> *cmdMap;

public:
    explicit Parser(unordered_map<string, Command *> *);

    ~Parser();

    int parseCommand(list<string>::iterator);

    static unordered_map<string, int> parseXml(const char *);

    static unordered_map<int, float> parseServerOutput(string incoming);

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PARSER_H_
