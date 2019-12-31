//

#include "MainThread.h"

/** Instantiate the main (first) scope.
 *
 */
MainThread::MainThread() {
    this->symTable = new SymbolTable();
}

/** Instantiate a new sub-scope.
 *
 * @param table
 */
MainThread::MainThread(SymbolTable *table) {
    this->symTable = new SymbolTable(table);
}

MainThread::~MainThread() {
    delete this->symTable;
    delete this->parser;
    this->cmdMap->clear();
}

/** Command interface forces to implement execute with iterator, so made this 1
 * for convenience.
 *
 * @return
 */
int MainThread::execute() {
    list<string>::iterator it;
    return execute(it);
}

/** Parses each line in the text file and executes using the parser.
 *  Also acts as the main thread where Server and Client are detaching from.
 *
 * @return 0 if no errors.
 */
int MainThread::execute(list<string>::iterator) {
    list<string> tokens;
    list<string>::iterator it;

    // Init commands map and give it to new Parser object.
    initCommands();
    this->parser = new Parser(cmdMap);

    // Turn file into tokens.
    tokens = Lexer::analyzeCode("../fly.txt");
    // Each iteration executes a line from the '.txt' file.
    for (it = tokens.begin(); it != tokens.end();) {
        advance(it, parser->parseCommand(it));
    }

    return 0;
}

/** Initializes the commands map.
 *
 * @param map to initialize
 * @param symTable, some commands need to initialize.
 */
void MainThread::initCommands() {
    cmdMap->emplace("openDataServer", new OpenServerCommand(symTable, programState));
    cmdMap->emplace("connectControlClient", new ConnectCommand(symTable, programState));
    cmdMap->emplace("var", new DefineVarCommand(symTable));
    cmdMap->emplace("Print", new Print());
    cmdMap->emplace("Sleep", new Sleep());
    cmdMap->emplace("while", new LoopCommand(new MainThread(this->symTable)));
    cmdMap->emplace("if", new IfCommand(new MainThread(this->symTable)));
}