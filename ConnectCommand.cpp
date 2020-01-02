//

#include "ConnectCommand.h"


using namespace std;

//
// Created by Dor on 19/12/2019.

ConnectCommand::ConnectCommand(SymbolTable *symbolTable, ProgramState *state)
        : symbolTable(symbolTable), programState(state) {}

int ConnectCommand::execute(list<string>::iterator it) {
    ++it;
    string tempIp = *it;
    tempIp.erase(0,1);
    tempIp.pop_back();
    const char *ip = (tempIp).c_str();
    ++it;
    string portString = *it;
    int port;
    try {
        port = stoi(portString);
    } catch (...) {
        programState->turnOff();
        throw "Port not valid";
    }

    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        programState->turnOff();
        throw "Failed to create client socket";
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    while ((this->isConnect = connect(clientSocket, (struct sockaddr *) &address, sizeof(address)))) {
//        if (isConnect == -1) {
//            programState->turnOff();
//            throw "Failed to connect to client server";
//        }
        this_thread::sleep_for(100ms);
    }

    thread th(&ConnectCommand::startSending, this);
    th.detach();
    return 3;
}

void ConnectCommand::startSending() {
    map<string, float> outgoing = symbolTable->getOutgoing();
    symbolTable->clearOutgoing();
    chrono::milliseconds duration, timePassed;
    chrono::steady_clock::time_point start, end;
    duration = chrono::milliseconds(100);

    while (programState->getState()) {
        // Start clock
        start = chrono::steady_clock::now();

        if (!outgoing.empty()) {
            auto it = outgoing.begin();
            while (it != outgoing.end()) {
                string command;
                string simLoaction = it->first;
                simLoaction.erase(0,5);
                simLoaction.pop_back();
                simLoaction.pop_back();
                command = "set " + simLoaction + " " + to_string(it->second) + "\r\n";
                const char *temp = command.c_str();
                int isSent = send(clientSocket, temp, strlen(temp), 0);
                if (isSent == -1) {
                    programState->turnOff();
                    throw "Failed to send string to host";
                }
                char buffer[1024] = {0};
                read(clientSocket, buffer, 1024);
//                clog << buffer << endl;
                it++;
            }
        }
        outgoing = symbolTable->getOutgoing();
        symbolTable->clearOutgoing();

        // End clock and then calculate time passed.
        end = chrono::steady_clock::now();
        timePassed = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Loop every 0.1s minimum, if time passed is longer then 0.1s continue.
        if (duration.count() - timePassed.count() > 0) {
            this_thread::sleep_for(duration - timePassed);
        }
    }
    close(clientSocket);
}

void ConnectCommand::addToCmdQueue(const char *temp) {
    ConnectCommand::cmdQueue.push_front(temp);
}

void ConnectCommand::addToCmdQueue(string str) {
    const char *temp = str.c_str();
    ConnectCommand::addToCmdQueue(temp);
}

void ConnectCommand::setState(ProgramState *state) {
    programState = state;
}
