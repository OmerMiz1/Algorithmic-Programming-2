//

#include "ConnectCommand.h"
#include <utility>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

using namespace std;

//
// Created by Dor on 19/12/2019.

ConnectCommand::ConnectCommand(const SymbolTable &symbolTable) : symbolTable(symbolTable) {}

int ConnectCommand::execute(list<string>::iterator it) {
    ++it;
    const char *ip = (*it).c_str();
    ++it;
    string portString = *it;
    int port;
    try {
        port = stoi(portString);
    } catch (...) {
        throw "Port not valid";
    }
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Failed to create client socket";
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    int isConnect = connect(clientSocket, (struct sockaddr *) &address, sizeof(address));
    if (isConnect == -1) {
        throw "Failed to connect to client server";
    }
    thread th(ConnectCommand::startSending, clientSocket, this->symbolTable);
    th.detach();
    return 3;
}

void ConnectCommand::startSending(int clientSocket, SymbolTable *symbolTable1) {
    map<string, float> outgoing = symbolTable1->getOutgoing();
    symbolTable1->clearOutgoing();
    //TODO send to client correctly + get variables from symbolTable
//    if (!ConnectCommand::cmdQueue.empty()) {
//        auto it = cmdQueue.begin();
//        while (it != cmdQueue.end()) {
//            int isSent = send(clientSocket, *it, strlen(*it), 0);
//            if (isSent == -1) {
//                throw "Failed to send string to host";
//            }
//            char buffer[1024] = {0};
//            read(clientSocket, buffer, 1024);
//            clog << buffer << endl;
//        }
//    } else {
//        this_thread::sleep_for(100ms);
//    }
}

void ConnectCommand::addToCmdQueue(string str) {
    const char *temp = str.c_str();
    ConnectCommand::addToCmdQueue(temp);
}

void ConnectCommand::addToCmdQueue(const char * temp) {
    ConnectCommand::cmdQueue.push_front(temp);
}
