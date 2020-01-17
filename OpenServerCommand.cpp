//
// Created by omer on 19/12/2019.
//

#define MAX_CHARS 1024
#define MAX_CLIENTS 1
#define FLOAT_MAX_DIGS 15

#include "OpenServerCommand.h"

OpenServerCommand::OpenServerCommand(SymbolTable *sym, ProgramState *state)
        : symTable(sym), programState(state) {}

OpenServerCommand::~OpenServerCommand() {
    delete symTable; // MainThread will delete programState object.
}

/** Starts a new TCP server.
 *
 * @param it points to "OpenServerCommand" token followed by "<port_val>"
 * @return number of tokens to advance in main loop.
 */
int OpenServerCommand::execute(list<string>::iterator it) {
    uint16_t port;
    sockaddr_in address{};

    ++it;
    // Parse port token
    try {
        port = stoi(*it);
    } catch (const char *e) {
        throw e;
    }

    // OPEN SOCKET
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        programState->turnOff();
        this->done = true;
        throw "Could not create a socket.";
    }

    address.sin_family = AF_INET; // address is in IPv4
    address.sin_addr.s_addr = INADDR_ANY; // give me any ip alloc'd for machine
    address.sin_port = htons(port); // more info tirgul 6 page 32

    // BIND
    if (::bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        programState->turnOff();
        this->done = true;
        throw "Could not bind the socket to an IP";
    }

    // LISTEN
    if (listen(sockfd, MAX_CLIENTS) == -1) {
        programState->turnOff();
        this->done = true;
        throw "Error listening to to port";
    }

    // ACCEPT
    while (!(client_sock = accept(sockfd,(struct sockaddr *) &address,(socklen_t *) &address))) {
        if (client_sock == -1) {
            programState->turnOff();
            this->done = true;
            throw "Error accepting simulator";
        }
    }
    cout << "Server: simulator accepted successfully" << endl;

    // IF ALL OK, CREATE LISTENING THREAD
    try {
        thread th(&OpenServerCommand::startListening, this);
        th.detach();
    } catch (const char *e) {
        programState->turnOff();
        this->done = true;
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
    unsigned int maxVars, totalBytesRead = 0, minBytes;
    chrono::milliseconds maxSleep, timePassed;
    chrono::steady_clock::time_point start, end;
    auto *tokens = new list<string>;
    auto *newVals = new unordered_map<int, float>;

    maxVars = Parser::parseXml("../generic_small.xml").size();
    minBytes = (FLOAT_MAX_DIGS + 1) * maxVars; // +1 for ',' delimiter.
    maxSleep = chrono::milliseconds(100); // Max sleep time

    // The listening loop, will break only if running will become false.
    while (programState->getState()) {
        // Start clock
        start = chrono::steady_clock::now();

        // Re-initialize every iteration
        int bytesRead = 0;
        char buffer[MAX_CHARS] = {0};
        string bufStr;

        // Optimization: if tokens is larger then 3 times max amount, clean it.
        if (tokens->size() > maxVars * 3) {
            clearOldTokens(tokens);
        }

        do {
            bytesRead += read(client_sock, buffer, MAX_CHARS);

            // Error reading
            if (bytesRead == -1) {
                programState->turnOff();
                this->done = true;
                throw "Error reading from simulator.";
            }

            totalBytesRead += bytesRead;
            toTokens(buffer, tokens);
        } while (totalBytesRead < minBytes);

        mapTokens(tokens, newVals);
        updateIngoing(newVals);

        // Clear current updates
        newVals->clear();

        // End clock and then calculate time passed.
        end = chrono::steady_clock::now();
        timePassed = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Read from server at-most 10 times a second (can be less)
        if (maxSleep.count() - timePassed.count() > 0) {
            this_thread::sleep_for(maxSleep - timePassed);
        }
    }
    close(this->sockfd);
    this->done = true;
}

/** Parses input from simulator into a list of floats.
 *
 * @param buffer as read from simulator
 * @param list to insert all float tokens
 */
void OpenServerCommand::toTokens(const char *buffer, list<string> *list) {
    regex floatRx("(-?\\d+\\.\\d+)|(\n)");
    string bufStr(buffer);

    auto start = sregex_iterator(bufStr.begin(), bufStr.end(), floatRx);
    auto end = sregex_iterator();

    for (sregex_iterator it = start; it != end; ++it) {
        smatch m = *it;
        string s = m.str();
        list->push_back(s);
    }
}

/** Generates an index:value map.
 *
 * The indexing is done in according to the generic_small.xml file (by the order
 * of each path in the file). List parameter should be generated by toTokens().
 *
 * @param tokens list of string tokens to be mapped.
 * @param map result
 */
void OpenServerCommand::mapTokens(list<string> *tokens,
                                  unordered_map<int, float> *map) {
    for (int i = 0; !tokens->empty() && tokens->front() != "\n";
         ++i, tokens->pop_front()) {
        map->emplace(i, stof(tokens->front()));
    }

    // Case tokens isn't empty, then front() is "\n"
    if (!tokens->empty()) {
        tokens->pop_front();
    }
}

/** Updates variables that belongs to SymbolTable.ingoing list.
 *
 * The map parameter should be generated by mapTokens() function.
 *
 * @param updates a map with new values.
 */
void OpenServerCommand::updateIngoing(unordered_map<int, float> *updates) {
    unordered_map<string, int>
            pathToIndex = Parser::parseXml("../generic_small.xml");

    // <Name : Path>
    for (auto const namePath : symTable->getIngoing()) {
        // <Path, Index>
        auto pathIndex = pathToIndex.find(namePath.second);
        // Used casting cause of warning, in reality its always positive.
        if (pathIndex != pathToIndex.end()
            && static_cast<unsigned>(pathIndex->second) < updates->size()) {
            // <Index : New Value>
            auto indexNewValue = updates->find(pathIndex->second);
            symTable->setVariable(namePath.first, indexNewValue->second);
        }
    }
}

/** Removes all tokens not related to latest read() from simulator.
 *
 * Used mainly for optimising. List should be generated using toTokens().
 *
 * @param tokens list of string tokens to update.
 */
void OpenServerCommand::clearOldTokens(list<string> *tokens) {
    auto it = tokens->end();
    // Finds last occurrence of '\n'
    for (--it; it->compare("\n"); --it) {}
    tokens->erase(tokens->begin(), it);
}
