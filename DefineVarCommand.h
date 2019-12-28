//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_

#include "Command.h"
#include <string>
#include <unordered_map>

using namespace std;

class DefineVarCommand : public Command {
private:
    unordered_map<string, pair<string, string> > remoteVariables; // map of <name, pair<direction, simLocation> >
    unordered_map<string, float > localVariables; // map of <name, value>
public:
    DefineVarCommand();

    int execute(list<string>::iterator) override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
