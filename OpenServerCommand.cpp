//
// Created by omer on 19/12/2019.
//

#define MAX_CHARS 1024
#define MAX_CLIENTS 1

#include "OpenServerCommand.h"
#include <algorithm>

using namespace std;

OpenServerCommand::OpenServerCommand(SymbolTable *sym, ProgramState *state)
        : symTable(sym), programState(state) {}

/** Creates a listening socket, listen to socket with independent thread.
 *
 * @param it points to "OpenServerCommand" token followed by "<port_val>"
 * @return number of tokens to advance in main loop.
 */
int OpenServerCommand::execute(list<string>::iterator it) {
    int port = 0;
    sockaddr_in address{};

    // Parse port token
    ++it;
    port = stoi(*it);

    // OPEN SOCKET
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        programState->turnOff();
        throw "Could not create a socket.";
    }

    address.sin_family = AF_INET; // address is in IPv4
    address.sin_addr.s_addr = INADDR_ANY; // give me any ip alloc'd for my machine
    address.sin_port = htons(port); // more info tirgul 6 page 32

    // BIND
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        programState->turnOff();
        throw "Could not bind the socket to an IP";
    }

    // LISTEN
    if (listen(sockfd, MAX_CLIENTS) == -1) {
        programState->turnOff();
        throw "Error listening to to port";
    }

    // ACCEPT
    while (!(this->client_sock = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &address))) {
        if (client_sock == -1) {
            programState->turnOff();
            throw "Error accepting client";
        }
    }

    // IF ALL OK, CREATE LISTENING THREAD
    try {
        thread th(&OpenServerCommand::startListening, this);
        th.detach();
    } catch (const char *e) {
        programState->turnOff();
        throw e;
    }

    return 2;
}

/** Listens to simulator requests 10 times a second and update the variables
 * that were defined to be updated in the '.txt' file.
 *
 * @param client_sock client's socket generated at OpenServerCommand::execute().
 * @param symTable to update.
 */
void OpenServerCommand::startListening() {
    int valRead;

    // Initialize clock variables for putting thread to sleep.
    chrono::milliseconds duration, timePassed;
    chrono::steady_clock::time_point start, end;
    duration = chrono::milliseconds(100);
    unordered_map<string, int> pathToIndexMap = Parser::parseXml("../generic_small.xml");
    unordered_map<int, float> *newVals = new unordered_map<int, float>;
    list<string> *tokens = new list<string>;

    // The listening loop, will break only if running will become false.
    while (programState->getState()) {
        // Start clock
        start = chrono::steady_clock::now();
        char buffer[MAX_CHARS];

        // Read to buffer until the entire message is received (might be cut midway)
        do {
            valRead = read(client_sock, buffer, MAX_CHARS);
            // Error reading
            if (valRead < 0) {
                programState->turnOff();
                throw "Error reading from simulator.";
            }
            toTokens(buffer, tokens);
        //loop ends if curr buffer includes '\n'.
        } while (!containsEol(buffer));

        string s;
        // In-case any new-line chars sneaked in to the front somehow.
        while(!tokens->empty()) {
            s = tokens->front();
            if(s == "\n") {
                tokens->pop_front();
            }
        }

        // Generate index:value map for current sample from server.
        for(int i = 0;s != "\n"; ++i, s= tokens->front()) {
            newVals->emplace(i, stof(s));
            tokens->pop_front();
            if(tokens->empty()) {
                break;
            }
        }

        // Update variables declared '<-' in the global SymbolTable.
        for (auto pair : symTable->getIngoing()) {
            /* pair.first == "name" , pair.second == "path"
             * newVals.first == "index", newVals.second == "value"
             * */
            auto curr = pathToIndexMap.find(pair.second);
            if(curr != pathToIndexMap.end()) {
                auto currNew = newVals->find(curr->second);
                symTable->setVariable(pair.first, currNew->second);
            }
        }
        newVals->clear();

        // End clock and then calculate time passed.
        end = chrono::steady_clock::now();
        timePassed = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Read from server at-most 10 times a second (can be less)
        if (duration.count() - timePassed.count() > 0) {
            this_thread::sleep_for(duration - timePassed);
        }
    }

    close(this->sockfd);
}

void OpenServerCommand::toTokens(char* buffer, list<string> *list) {
    regex floatRx("(-?\\d+\\.\\d+)|(\n)");
    string bufStr(buffer);

    auto start = sregex_iterator(bufStr.begin(), bufStr.end(), floatRx);
    auto end = sregex_iterator();

    for(sregex_iterator it = start; it != end; ++it) {
        smatch m = *it;
        list->push_back(m.str());
    }
}
/*


*/
/**
 *
 * @param OpenServerCommand sends the incoming string. String looks like:
 * {0.0,32.4,33.1,....} and should have 36 or so floats.
 * @return Map<INDEX, VALUE> with updated values from serer.
 *//*

void OpenServerCommand::parseIncoming(char* buffer, unordered_map<int, float> *currVals, unordered_map<int, float> *nextVals, int* index) {
    char* token;
    for(token = strtok(buffer, ","); token != NULL; token = strtok(NULL, ",")) {
        if(isFloat(token)) {
            currVals->emplace((*index), stof(token));
            ++(*index);
        } else if (containsEol(token)) {
            string temp(token);
            size_t eol = temp.find_first_of('\n');
            currVals->emplace((*index), stof(temp.substr(0, eol-1)));
            (*index) = 0;

            if(temp.length() == eol+1) {
                return;
            }

            nextVals->emplace((*index), stof(temp.substr(eol+1, temp.length())));
            ++(*index);
            break;
        }
    }

    for(; token!=NULL; token = strtok(NULL, ",")) {
        if(isFloat(token)) {
            nextVals->emplace((*index), stof(token));
            ++(*index);
        }
    }
}

bool OpenServerCommand::isFloat(string str) {
    regex floatRx("(-?\\d+\\.\\d+)");
    return regex_match(str, floatRx);
}
*/

bool OpenServerCommand::containsEol(char* buffer) {
    string temp(buffer);
    return (temp.find_first_of('\n') != string::npos);
}

