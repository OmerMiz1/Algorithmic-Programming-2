//

#include "ConnectCommand.h"


using namespace std;

//
// Created by Dor on 19/12/2019.

ConnectCommand::ConnectCommand(SymbolTable *symTable, ProgramState *programState)
        : symbolTable(symTable), programState(programState) {}

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
        if(this->isConnect == -1) {
            throw "Error connecting to simulator";
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout<<"Client: connected to simulator successfully"<<endl;

    thread th(&ConnectCommand::startSending, this);
    th.detach();
    return 3;
}

void ConnectCommand::startSending() {
    map<string, float> outgoing = symbolTable->getOutgoing();
    chrono::milliseconds duration, timePassed;
    chrono::steady_clock::time_point start, end;
    duration = chrono::milliseconds(100);
    //this method runs as a thread, she returns only when the program state is changed to false
    while (programState->getState()) {
        // Start clock
        start = chrono::steady_clock::now();
        //if there are commands to send to the simulator
        if (!outgoing.empty()) {
            auto it = outgoing.begin();
            //iterates over the commands and send them
            while (it != outgoing.end()) {
                string command;
                string simLocation = it->first;
                //"builds" the command according to how the simulator is used to get it
                command = "set " + simLocation + " " + to_string(it->second) + "\r\n";
                //converts the command to type const char*
                const char *temp = command.c_str();
                //sends the command and saves the approval of the simulator
                ssize_t isSent = send(clientSocket, temp, strlen(temp), 0);
                //check if the command sent correctly
                if (isSent == -1) {
                    //if couldn't send the command set the state to false and throw an error
                    programState->turnOff();
                    throw "Failed to send string to host";
                }
                char buffer[1024] = {0};
                //gets a response from the simulator
                read(clientSocket, buffer, 1024);
                //for logging purposes in the future
                //clog << buffer << endl;
                it++;
            }
        }
        //check if there's a new command in the outgoing of the symbol table
        outgoing = symbolTable->getOutgoing();

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

ConnectCommand::~ConnectCommand() {}
