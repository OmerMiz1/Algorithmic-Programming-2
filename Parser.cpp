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