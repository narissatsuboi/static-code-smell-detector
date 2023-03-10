#include "Function.h"
#include "StringUtility.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include <set>

#include "Detector.h"

const int LONG_METHOD_THRESHOLD = 15;

const int LONG_PARAM_THRESHOLD = 3;

Detector::Detector(string &filepath) {
    this->file = filepath;
    buildFunctionList();
}


bool Detector::isDelimiter(char &c) {
    const unordered_set<char> DELIMS({')', '(', '}', '{', ']', '['});
    return DELIMS.count(c);
}

bool Detector::hasParenthesesPair(string &s) {
    unordered_map<char, char> CLOSED({{')', '('},
                                      {'}', '{'},
                                      {']', '['}});
    unordered_map<char, int> freq({{')', 0},
                                   {'}', 0},
                                   {']', 0}});
    unordered_map<char, int>::iterator it;
    vector<char> stack = {};
    bool isBalanced = true;
    for (char &c: s) {
        if (!isDelimiter(c))
            continue;
        if (CLOSED.count(c)) {
            if (!stack.empty() && stack.back() == CLOSED[c]) {
                stack.pop_back();
                it = freq.find(c);
                it->second++;
            } else {
                isBalanced = false;
            }
        } else
            stack.push_back(c);
    }
    //TODO need to update if a function declaration will extend multiple lines
    if (!isBalanced) {
        return false;
    }
    return freq[')'] == 1;
}

void Detector::buildFunctionList() {
    string line, name;
    int lineNo = 0;
    string fullSig, handle;
    ifstream inFile(this->file);
    while (getline(inFile, line)) {
        lineNo++;
        StringUtility::trimToSignature(line);
        if (skipLine(line)) {
            continue;
        }
        if (hasParenthesesPair(line)) {
            this->functionList.emplace_back(line, lineNo);
        }
    }
    inFile.close();
}

bool Detector::skipLine(string &line) {
    return (isBlankLine(line) || isComment(line) || hasInvalidFirstToken(line));
}

bool Detector::hasInvalidFirstToken(string &s) {
    const unordered_set <string> INVALID({"case", "class", "else", "if", "struct", "switch", "return", "throw", "while"});
    string token = s.substr(0, s.find_first_of(' '));
    return INVALID.count(token);
}

bool Detector::isBlankLine(string &s) {
    return s.length() == 0;
};

bool Detector::isComment(string &s) {
    unordered_set<char> SKIP({'#', '/', '*'});
    return SKIP.count((s.at(0)));
}

bool Detector::isLongMethod(Function &function) const {
    const unordered_set<char> delims({'}', '{'});
    ifstream inFile(this->file);
    string line;
    int lineNo = 0;
    int matchesMade = 0;
    unordered_map<char, char> CLOSED({{'}', '{'}});

    vector<char> stack = {};
    do {
        lineNo++;
        if (lineNo < function.start) {
            continue;
        }
        for (char &c: line) {
            if (!delims.count(c))
                continue;
            if (CLOSED.count(c)) {
                if (!stack.empty() && stack.back() == CLOSED[c]) {
                    stack.pop_back();
                    matchesMade++;
                }
            } else
                stack.push_back(c);
        }
        if (stack.empty() && matchesMade > 0) {
            function.end = lineNo - 1;
            function.loc = function.end - function.start + 1;
            if (function.loc > LONG_METHOD_THRESHOLD) {
                function.longmethod = true;
                return true;
            }
            break;
        }
    } while (getline(inFile, line));
    inFile.close();
    return false;
}

void Detector::detectLongMethods() {
    for (auto &f: this->functions) {
        isLongMethod(f);
    }
}



