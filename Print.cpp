//
// Created by omer on 20/12/2019.
//

#include <string>
#include <iostream>
#include "Print.h"
using namespace std;

/*
 * Print assumes that lexed string array has its message AS IS, no delimiters.
 * Jumps: 2 elements - Print + <message> 
 */
int Print::execute() {
  cout << msg << endl;
  return 2;
}
