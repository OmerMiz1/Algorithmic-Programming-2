//
// Created by Dor Refaeli on 28/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT_SYMBOLTABLE_H
#define ALGORITHMICPROGRAMMINGPROJECT_SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include <map>
#include <mutex>

using namespace std;

class SymbolTable {
    //the father-SymbolTable, if null this is the main SymbolTable
    SymbolTable *father;
    //a map that contains the remote variables <name, pair<direction, simLocation>>
    unordered_map<string, pair<string, string> > remoteVariables;
    //a map that contains the local variables and their values <name, value>
    unordered_map<string, float> localVariables;
    //a map that contains the variables that should be updated by the OpenServerCommand
    map<string, string> ingoing;
    //a map that contains the variables that should be sent to the simulator by the ConnectCommand
    map<string, float> outgoing;

public:
    /**
     * Construct a main-SymbolTable
     */
    SymbolTable();

    /**
     * Construct a sub-SymbolTable that as a father-SymbolTable
     * @param father the father-SymbolTable
     */
    explicit SymbolTable(SymbolTable *);

    /**
     * Get a variable according to his name
     *     if the name is an expression evaluate him and returns his value
     * @param name the name of the desired variable
     * @return the value of the desired variable as a float
     */
    float getVariable(string);

    /**
     * Sets a new value for a variable
     * @param name the name of the variable
     * @param value the new value of the variable
     */
    void setVariable(string, float);

    /**
     * Adds a variable to the remote map
     * @param name the name of the variable
     * @param direction the direction of the remote variable
     * @param simLocation the location of the variable at the simulator
     */
    void setRemoteVariable(string, string, string);

    /**
     * Check if the symbol table contains the variable (as a local)
     * @param name the name of the variable we are searching for
     * @return true if the symbol table contains the variable, false otherwise
     */
    bool contains(string);

    /**
     * Check if the symbol table or his father contains the variable (as a local)
     * @param name the name of the variable we are searching for
     * @return true if the symbol table contains the variable, false otherwise
     */
    bool recursiveContains(string);

    /**
     * Returns a map that contains the name of the ingoing variables and their path
     * to be used by OpenServerCommand
     * @return the map of ingoing variables
     */
    map<string, string> getIngoing();

    /**
     * Returns a map that contains the names an paths of the variables that need to be sent to the simulator
     * then delete the all of the map content
     * to be used by ConnectCommand
     * @return the map of outgoing variables
     */
    map<string, float> getOutgoing();

    /**
     * Returns an updated map of the local variables
     * to be used when there is a need of evaluting an expression
     * @return the updated map of local variables
     */
    map<string, float> updatedMap();

private:

    /**
     * Delete all of the content of the outgoing map
     */
    void clearOutgoing();

    /**
     * Adds a variables to the map of ingoing
     * @param name the name of the variable
     * @param simLocation the location of the variable in the simulator
     */
    void addToIngoing(string name, string simLocation);

    /**
     * Checks if a variable need to be sent to the map of outgoing, adds him if needed
     * @param name the name of the variable
     * @param num the value of the variable
     */
    void addToOutgoingIfNeeded(string name, float num);
};


#endif //ALGORITHMICPROGRAMMINGPROJECT_SYMBOLTABLE_H
