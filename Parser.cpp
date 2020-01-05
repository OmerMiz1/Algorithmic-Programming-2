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
    auto currCmd = this->cmdMap->find(*it);

    // Cmd found in map, just executes
    if (currCmd != this->cmdMap->end()) {
        return currCmd->second->execute(it);
    // Cmd not in map so it is an assignment.
    } else {
        return this->cmdMap->find("var")->second->execute(it);
    }
    //TODO support FunctionCommands when done. can be done by inserting the assignment
    // if into an else if (symVariable.contains(it)) and adding else for function name
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
    regex varPathRx("\\s*<node>(.*)<\\/node>");

    // Iterates each line in XML, index each path accordingly.
    for (int index = 0; getline(file, str);) {
        if (regex_search(str, match, varPathRx)) {
            string temp = "sim(";
            temp.append(match[1]);
            temp.append(")");
            symTable.emplace(match[1], index);
            index++;
        }
    }

    file.close();
    return symTable;
}