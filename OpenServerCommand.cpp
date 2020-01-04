//
// Created by omer on 19/12/2019.
//

#define MAX_CHARS 1024
#define MAX_CLIENTS 1
#define FLOAT_MAX_DIGS 15

#include "OpenServerCommand.h"

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
            throw "Error accepting simulator";
        }
    }
    cout<<"Server: simulator accepted successfully"<<endl;

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
    int bytesRead, maxVarCount = Parser::parseXml("../generic_small.xml").size();
    // Maximal chars in float string + 1 for ',' times max ingoing variables.
    int minBytes = (FLOAT_MAX_DIGS+1)*maxVarCount;

    // Initialize clock variables for putting thread to sleep.
    chrono::milliseconds duration, timePassed;
    chrono::steady_clock::time_point start, end;
    duration = 100ms;
    unordered_map<int, float> *newVals = new unordered_map<int, float>;
    list<string> *tokens = new list<string>;

    // The listening loop, will break only if running will become false.
    while (programState->getState()) {
        // Start clock
        start = chrono::steady_clock::now();

        // Re-initialize every iteration
        char buffer[MAX_CHARS] = {0};
        bytesRead = 0;
        string bufStr("");

        if(tokens->size() > 100) {
            clearOldTokens(tokens);
        }

        do {
            bytesRead += read(client_sock, buffer, MAX_CHARS);
            toTokens(buffer, tokens);
        } while(0 <= bytesRead && bytesRead < minBytes);

        // Error reading
        if (bytesRead < 0) {
            programState->turnOff();
            throw "Error reading from simulator.";
        }

        mapTokens(tokens, newVals);
        updateIngoing(newVals);

        // Clear current updates
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

/** Parses input from simulator into a list of floats.
 *
 * @param buffer as read from simulator
 * @param list to insert all float tokens
 */
void OpenServerCommand::toTokens(const char* buffer, list<string> *list) {
    regex floatRx("(-?\\d+\\.\\d+)|(\n)");
    string bufStr(buffer);

    auto start = sregex_iterator(bufStr.begin(), bufStr.end(), floatRx);
    auto end = sregex_iterator();

    for(sregex_iterator it = start; it != end; ++it) {
        smatch m = *it;
        string s = m.str();
        list->push_back(s);
    }
}

/*Generate index:value map for current sample from server. In our case
          * should read 36 values and map them. Pop each value after mapped.*/
void OpenServerCommand::mapTokens(list<string> *tokens, unordered_map<int,float> *map) {
    for(int i =0; !tokens->empty() && tokens->front() != "\n"; ++i, tokens->pop_front()) {
        map->emplace(i, stof(tokens->front()));
    }

    if(!tokens->empty()) {
        tokens->pop_front();
    }
}

// Update variables declared '<-' in the global SymbolTable.
void OpenServerCommand::updateIngoing(unordered_map<int,float> *updates) {
    unordered_map<string, int> pathToIndex = Parser::parseXml("../generic_small.xml");

    // <Name : Path>
    for (auto namePath : symTable->getIngoing()) {
        // <Path, Index>
        auto pathIndex = pathToIndex.find(namePath.second);
        if(pathIndex != pathToIndex.end() && pathIndex->second < updates->size()) {
            // <Index : New Value>
            auto indexNewValue = updates->find(pathIndex->second);
            /*if(this->symTable->contains(namePath.first)) { //TODO remove before submition.
                cout << namePath.first;
                cout <<"   before: #"<<this->symTable->getVariable(namePath.first);
                cout << " after: $" << indexNewValue->second << endl;
            }*/
            symTable->setVariable(namePath.first, indexNewValue->second);
        }
    }
}

void OpenServerCommand::clearOldTokens(list<string> *tokens) {
    list<string>::iterator it = tokens->end();
    // Finds last occurrence of '\n'
    for(--it; it->compare("\n"); --it) {}
    tokens->erase(tokens->begin(), it);
}
