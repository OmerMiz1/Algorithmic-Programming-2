//

#include "MainThread.h"

/** Parses each line in the text file and executes using the parser.
 *  Also acts as the main thread where Server and Client are detaching from.
 *
 * @return 0 if no errors.
 */
int MainThread::execute() {
  Parser *parser;
  list<string> tokens;
  list<string>::iterator it;
  SymbolTable* symTable = new SymbolTable();
  unordered_map<string,Command*> cmdMap;

  // Init commands map and give it to new Parser object.
  initCommands(&cmdMap, symTable);
  parser = new Parser(cmdMap);

  // Turn file into tokens.
  tokens = Lexer::analyzeCode("../fly.txt");

  // Each iteration executes a line from the '.txt' file.
  for(it = tokens.begin(); it != tokens.end();) {
    advance(it, parser->parseCommand(it));
  }

  return 0;
}

/** Initializes the commands map.
 *
 * @param map to initialize
 * @param symTable, some commands need to initialize.
 */
void MainThread::initCommands(unordered_map<string, Command*> *map,SymbolTable *symTable) {
  map->emplace("OpenServerCommand", new OpenServerCommand(symTable));
  map->emplace("ConnectControlClient", new ConnectCommand(symTable));
  map->emplace("var", new DefineVarCommand(symTable));
  map->emplace("Print", new Print());
  map->emplace("Sleep", new Sleep());
  map->emplace("while", new LoopCommand(symTable));
  map->emplace("if", new IfCommand(symTable));
}

/*void MainThread::genMaps() {
  list<pair<string,Var*>>::iterator it1;
  list<pair<string,Command*>>::iterator it2;

  // Var map
  for(it1 = this->varList.begin(); it1 != this->varList.end(); ++it1) {
    this->varMap.emplace(it1->first, it1);
  }

  // Commands map
  for(it2 = this->cmdList.begin(); it2 != this->cmdList.end(); ++it1) {
    this->varMap.emplace(it1->first, it1);
  }
}*/