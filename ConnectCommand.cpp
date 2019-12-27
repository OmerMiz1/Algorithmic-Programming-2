//
// Created by Dor on 19/12/2019.
//

#include "ConnectCommand.h"
#include <utility>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

ConnectCommand::ConnectCommand(const char *port, const char *ip) {
    try {
        this->port = stoi(port);
    } catch (...) {
        throw "Port not valid";
    }
}

int ConnectCommand::execute(list<string>::iterator it) {
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Failed to create client socket";
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(this->ip);
    address.sin_port = htons(this->port);
    int isConnect = connect(clientSocket, (struct sockaddr *) &address, sizeof(address));
    if (isConnect == -1) {
        throw "Failed to connect to client server";
    }
    return 0;
}

void ConnectCommand::sendToHost(const char *str) {
    int isSent = send(this->clientSocket, str, strlen(str), 0);
    if (isSent == -1) {
        throw "Failed to send string to host";
    }
    char buffer[1024] = {0};
    read(this->clientSocket, buffer, 1024);
    clog << buffer << endl;
}

ConnectCommand::~ConnectCommand() {
    close(this->clientSocket);
}