//
// Created by Dor on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__LEXER_H_
#define ALGORITHMICPROGRAMMINGPROJECT__LEXER_H_

#include <string>
#include <cstdio>
#include <list>

using namespace std;

class Lexer {
public:
    /**
     * Analyzes a file and returns a list of string accordingly
     * @param file the path of the file that needs to be analyzed
     * @return a list of strings that describes the file by tokens
     */
    static list<string> analyzeCode(const char *file);

    /**
     * Analyzes a line and returns a list of string accordingly
     * @param str the line that needs to be analyzed
     * @return a list of strings that describes the line by tokens
     */
    static list<string> analyzeLine(string str);

private:
    /**
     * Check if a string is a prefix of another string
     * @param prefix the prefix we are checking for
     * @param str the string we are searching the prefix in
     * @return true if the first is a prefix of the secont, false otherwise
     */
    static bool startsWith(const char *prefix, string str);
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__LEXER_H_
