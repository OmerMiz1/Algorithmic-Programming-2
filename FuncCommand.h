//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__FUNCCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__FUNCCOMMAND_H_

#include "Command.h"
#include <string>
#include <list>

using namespace std;

class FuncCommand : public Command {
private:

public:
    int execute(list<string>::iterator) override;
    ~FuncCommand() {};
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__FUNCCOMMAND_H_
