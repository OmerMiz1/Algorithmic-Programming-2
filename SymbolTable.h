//
// Created by Dor Refaeli on 28/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT_SYMBOLTABLE_H
#define ALGORITHMICPROGRAMMINGPROJECT_SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include <map>
#include <mutex>

using namespace std;

class SymbolTable {
    SymbolTable *father;
    unordered_map<string, pair<string, string> > remoteVariables; // map of <name, pair<direction, simLocation> >
    unordered_map<string, float> localVariables; // map of <name, value>
    map<string, string> ingoing;
    map<string, float> outgoing;
    mutex mtx;

public:
    SymbolTable();

    explicit SymbolTable(SymbolTable *father);

    float getVariable(string);

    void setVariable(string, float);

    void setRemoteVariable(string, string, string);

    bool contains(string);

    bool recursiveContains(string);

    map<string, string> getIngoing();

    map<string, float> getOutgoing();

    map<string, float> updatedMap();

    void clearOutgoing();

private:
    void addToIngoing(string, string);

    void addToOutgoing(string, float);
};


#endif //ALGORITHMICPROGRAMMINGPROJECT_SYMBOLTABLE_H
