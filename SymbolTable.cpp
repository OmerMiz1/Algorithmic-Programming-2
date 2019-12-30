//
// Created by Dor Refaeli on 28/12/2019.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    this->father = nullptr;
}

SymbolTable::SymbolTable(SymbolTable *father) : father(father) {}

float SymbolTable::getVariable(string name) {
    lock_guard<mutex> lock(this->mtx);
    if (!this->recursiveContains(name)) {
        throw "Asked for non existing variable " + name;
    } else if (this->contains(name)) {
        return localVariables[name];
    } else if (this->father != nullptr) {
        return this->father->getVariable(name);
    }
    throw "Error getting a variable";
}

void SymbolTable::setVariable(string name, float num) {
    lock_guard<mutex> lock(this->mtx);
    if (!this->contains(name) && this->recursiveContains(name)) {
        this->father->setVariable(name, num);
    } else {
        this->localVariables[name] = num;
        this->addToOutgoing(name, num);
    }
}

void SymbolTable::setRemoteVariable(string name, string direction, string simLocation) {
    lock_guard<mutex> lock(this->mtx);
    this->remoteVariables[name] = make_pair(direction, simLocation);
    if (direction == "<-") {
        addToIngoing(name, simLocation);
    }
}

bool SymbolTable::contains(string name) {
    return this->localVariables.count(name);
}

bool SymbolTable::recursiveContains(string name) {
    if (this->father != nullptr) {
        return this->contains(name) || this->father->recursiveContains(name);
    } else {
        return this->contains(name);
    }
}

map<string, string> SymbolTable::getIngoing() {
    lock_guard<mutex> lock(this->mtx);
    return this->ingoing;
}

map<string, float> SymbolTable::getOutgoing() {
    lock_guard<mutex> lock(this->mtx);
    map<string, float> temp;
    auto it = this->outgoing.begin();
    while (it != this->outgoing.end()) {
        temp[it->first] = it->second;
    }
    return temp;
}

map<string, float> SymbolTable::updatedMap() {
    lock_guard<mutex> lock(this->mtx);
    map<string, float> temp;
    if (this->father != nullptr) {
        temp = this->father->updatedMap();
    }
    auto it = this->localVariables.begin();
    while (it != this->localVariables.end()) {
        temp[it->first] = it->second;
    }
    return temp;
}

void SymbolTable::addToIngoing(string name, string simLocation) {
    lock_guard<mutex> lock(this->mtx);
    this->ingoing[name] = simLocation;
}

void SymbolTable::addToOutgoing(string name, float num) {
    lock_guard<mutex> lock(this->mtx);
    if (this->father == nullptr) {
        if (this->remoteVariables.count(name)) {
            if (this->remoteVariables[name].first == "->") {
                this->outgoing[this->remoteVariables[name].second] = num;
            }
        }
    } else {
        this->father->addToOutgoing(name, num);
    }
}

void SymbolTable::clearOutgoing() {
    lock_guard<mutex> lock(this->mtx);
    this->outgoing.clear();
}
