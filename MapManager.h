//
// Created by omer on 20/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__MAPMANAGER_H_
#define ALGORITHMICPROGRAMMINGPROJECT__MAPMANAGER_H_

#include <unordered_map>
#include <string>
#include <mutex>

using namespace std;


/*
 * Generally this map supposed to handle gets and sets with threads.
 */

class MapManager {
 private:
  unordered_map<string,mutex> locksMap;
 public:
  int setVar();
  Command* getVar();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__MAPMANAGER_H_
