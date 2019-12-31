//
// Created by Dor on 19/12/2019.
//

#include "Lexer.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <list>
#include <algorithm>


using namespace std;

list<string> Lexer::analyzeCode(const char *file) {
    list<string> tokens;
    string str;
    ifstream fileStream(file);
    while (getline(fileStream, str)) {

        list<string> temp = analyzeLine(str);
        for (auto it : temp) {
            tokens.emplace_back(it);
        }
    }
    return tokens;
}

bool Lexer::startsWith(const char *prefix, string str) {
    const auto strBegin = str.find_first_not_of(" \t");
    const auto strEnd = str.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;
    str = str.substr(strBegin, strRange);
    std::string temp1(prefix);
    std::string temp2(str);
    auto res = std::mismatch(temp1.begin(), temp1.end(), temp2.begin());
    if (res.first == temp1.end()) {
        return true;
    }
    return false;
}

list<string> Lexer::analyzeLine(string str) {
    list<string> tokens;
    if (startsWith("openDataServer", str)) {
        regex re("\\s*openDataServer\\((.*)\\)");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("openDataServer");
        tokens.emplace_back(m[1]);
    } else if (startsWith("connectControlClient", str)) {
        regex re("\\s*connectControlClient\\((.*),(.*)\\)");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("connectControlClient");
        //TODO ip is parsed as \"127.0.0.1\"
        tokens.emplace_back(m[1]);
        tokens.emplace_back(m[2]);
    } else if (startsWith("var", str)) {
        regex re("\\s*var (.*) (->|<-) (.*)");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("var");
        if (m.empty()) {
            regex re("\\s*var (.*) = (.*)");
            regex_search(str, m, re);
            tokens.emplace_back(m[1]);
            tokens.emplace_back("=");
            tokens.emplace_back(m[2]);
        } else {
            tokens.emplace_back(m[1]);
            tokens.emplace_back(m[2]);
            tokens.emplace_back(m[3]);
        }
    } else if (startsWith("Print", str)) {
        regex re("\\s*Print\\((.*)\\)");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("Print");
        tokens.emplace_back(m[1]);
    } else if (startsWith("Sleep", str)) {
        regex re("\\s*Sleep\\((.*)\\)");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("Sleep");
        tokens.emplace_back(m[1]);
    } else if (startsWith("if", str)) {
        regex re("\\s*if (.*) \\{");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("if");
        tokens.emplace_back(m[1]);
    } else if (startsWith("while", str)) {
        regex re("\\s*while (.*) \\{");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back("while");
        tokens.emplace_back(m[1]);
    } else if (startsWith("}", str)) {
        tokens.emplace_back("}");
    } else {
        regex re("\\s*(.*) = (.*)");
        smatch m;
        regex_search(str, m, re);
        tokens.emplace_back(m[1]);
        tokens.emplace_back(m[2]);
    }
    return tokens;
}
