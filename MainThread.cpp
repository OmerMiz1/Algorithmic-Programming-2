//

#include "MainThread.h"

/** Instantiate the main (first) scope.
 *
 */
MainThread::MainThread(char* fileName) {
    this->filePath = fileName;
    this->symTable = new SymbolTable();
}

/** Instantiate a new sub-scope.
 *
 * @param table
 */
MainThread::MainThread(SymbolTable *table, MainThread *outer): father(outer) {
    this->filePath = outer->filePath;
    this->symTable = new SymbolTable(table);
}

MainThread::~MainThread() {
    delete symTable;
    delete cmdMap;
}

/** Command interface forces to implement execute with iterator, so made this 1
 * for convenience.
 *
 * @return
 */
int MainThread::execute() {
    list<string>::iterator dummy;
    return execute(dummy);
}

/** Parses each line in the text file and executes using the parser.
 *  Also acts as the main thread where Server and Client are detaching from.
 *
 * NOTE: This class is also used in order to call inner scopes such as in while
 * or if commands (yes its code smells, we have time limit after all).
 *
 * @return 0 if no errors.
 */
int MainThread::execute(list<string>::iterator it) {
    list<string> tokens;

    // Init commands map and give it to new Parser object.
    initCommands();
    Parser *parser = new Parser(cmdMap);

    // FIRST MAIN TOKEN ITERATION
    if (this->father == nullptr) {
        // Turn file into tokens.
        try {
            try {
                tokens = Lexer::analyzeCode(filePath.c_str());
            } catch (const char* e) {
                throw e;
            }

        } catch (const char* e) {
            throw e;
        }
        // Each iteration executes a line from the '.txt' file.
        for (it = tokens.begin(); it != tokens.end();) {
            advance(it, parser->parseCommand(it));
        }

    // Sub-MainThread execution, case of inner scope (code smells we know :\)
    } else {
        while(it->compare("}") != 0) {
            advance(it, parser->parseCommand(it));
        }
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
    cmdMap->emplace("Print", new Print(symTable));
    cmdMap->emplace("Sleep", new Sleep());
    cmdMap->emplace("while", new LoopCommand(new MainThread(symTable, this), symTable));
    cmdMap->emplace("if", new IfCommand(new MainThread(symTable,this), symTable));
}