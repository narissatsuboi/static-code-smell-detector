#include "Function.h"
#include "StringUtility.h"
#include "Detector.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <regex>


const int LONG_METHOD_THRESHOLD = 15;

const int LONG_PARAM_THRESHOLD = 3;

const double DUP_CODE_THRESHOLD = 0.75;

Detector::Detector(string &filepath) {
    this->file = filepath;
    buildFunctionList();
}


bool Detector::isDelimiter(char &c) {
    const unordered_set<char> DELIMS({')', '(', '}', '{', ']', '['});
    return DELIMS.count(c);
}

bool Detector::hasParenthesesPair(string &s) {
    unordered_map<char, char> CLOSED({{')', '('}});
    unordered_map<char, int> freq({{')', 0}});
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
        // TODO CONFIRM NOT A DECLARATION
        StringUtility::trimToSignature(line);
        if (skipLine(line)) {
            continue;
        }
        if (hasParenthesesPair(line)) {
            this->masterFunctionList.emplace_back(line, lineNo);
        }
    }
    inFile.close();
}

bool Detector::skipLine(string &line) {
    return (isBlankLine(line) || isComment(line) || hasInvalidFirstToken(line));
}

bool Detector::hasInvalidFirstToken(string &s) {
    const unordered_set <string> INVALID({"case", "class", "for", "else", "if", "struct", "switch", "return", "throw", "while"});
    string token = s.substr(0, s.find_first_of('('));
    StringUtility::trimWhitespace(token);
    return INVALID.count(token);
}

bool Detector::isBlankLine(string &s) {
    return s.length() == 0;
}

bool Detector::isComment(string &s) {
    unordered_set<char> SKIP({'#', '/', '*'});
    return SKIP.count((s.at(0)));
}

bool Detector::isLongMethod(Function &function) const {
    findEOFunction(function);
    function.loc = ((function.end - function.start) - function.blanks) + 1;
//    function.loc = function.end - function.start + 1;
    if (function.loc > LONG_METHOD_THRESHOLD) {
        function.longFunction = true;
        return true;
    }
    return false;
}

void Detector::findEOFunction(Function &function) const {
    const unordered_set<char> delims({'}', '{'});
    ifstream inFile(this->file);
    string line;
    int lineNo = 0;
    int matchesMade = 0;
    unordered_map<char, char> CLOSED({{'}', '{'}});
    bool EOFFound = false;
    vector<char> stack = {};
    do {
        getline(inFile, line);
        lineNo++;
        if (lineNo < function.start) {
            continue;
        }
        if (isBlankLine(line)) {
            function.blanks++;
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
            function.end = lineNo;
            EOFFound = true;
        }
    } while (!EOFFound);
    inFile.close();
}

void Detector::detectLongMethods() {
    for (auto &f: this->functionList) {
        isLongMethod(f);
    }
}

void Detector::detectLongParameterList() {
    for (auto &f: this->functionList) {
        isLongParameterList(f);
    }
}

void Detector::isLongParameterList(Function &function) {
    string sig = function.signature;
    string::difference_type n = count(sig.begin(), sig.end(), ',');
    function.paramCount = n + 1;
    if (function.paramCount <= LONG_PARAM_THRESHOLD) {
        function.longParam = false;
    } else {
        function.longParam = true;
    }
}

void Detector::detectDuplicatedCode() {
    // find end index of each function, store to function
    for (auto &f: functionList) {
        findEOFunction(f);
    }

    // get stringified version and store to function
    for (auto &f: functionList) {
        stringifyFunction(f);
    }

    // find fs with same char count and get the hamming ratio
    for (auto i = 0; i < functionList.size(); i++) {
        Function &f1 = functionList[i];
        for (auto j = i + 1; j < functionList.size(); j++) {
            Function &f2 = functionList[j];
            isDuplicatedCode(f1, f2);
        }
    }
}

void Detector::isDuplicatedCode(Function &f1, Function &f2) {
    if (f1.charCount == f2.charCount) {
        double similarity = 1.0 - hammingRatio(f1.stringified, f2.stringified);
        if (similarity >= DUP_CODE_THRESHOLD) {
            dups.insert(dups.end(), {f1.handle, f2.handle});
        }
    }
}

void Detector::printFunctions() {
    string bannerContent = "Functions To Analyze List";
    cout << StringUtility::banner(bannerContent);
    for (auto &f: functionList)
        cout << f << "\n";
}

void Detector::stringifyFunction(Function &function) const {
    ifstream inFile(this->file);
    string ss, line;
    int lineNo = 0;

    regex r("\\s+");

    while (lineNo < function.end + 1) {
        lineNo++;
        getline(inFile, line);

        if (lineNo < function.start) {
            continue;
        }

        ss += regex_replace(line, r, "");
    }
    inFile.close();
    ss.erase(0, ss.find('{'));
    function.stringified = ss;
    function.charCount = function.stringified.length();
}

double Detector::hammingRatio(string &s1, string &s2) {
    double count = 0, l = s1.length();
    for (auto i = 0; i < l; i++) {
        if (s1[i] != s2[i])
            count++;
    }
    return count / l;
}
