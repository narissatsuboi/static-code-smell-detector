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

/* THRESHOLDS PER SPECIFICATION */

const int LONG_METHOD_THRESHOLD = 15;
const int LONG_PARAM_THRESHOLD = 3;
const double DUP_CODE_THRESHOLD = 0.75;

/* GLOBALS */

const char LPAREN = '(', RPAREN = ')';
const char LCURL = '{', RCURL= '}';
const char LBRACK = '[', RBRACK = ']';
unordered_set<char> COMMENT_START({'#', '/', '*'});
const unordered_set<char> BRACKETS({LPAREN, RPAREN, LCURL, RCURL, LBRACK, RBRACK});
const unordered_set <string> INVALID({"case", "class", "for", "else", "if",
                                      "struct", "switch", "return", "throw",
                                      "while"});

/**
 * Construct new Detector and build master function list member.
 */
Detector::Detector(string &filepath) {
    this->file = filepath;
    buildFunctionList();
}


bool Detector::isBracket(char &c) { return BRACKETS.count(c); }

/**
 * Returns true if the string has a single pair of parentheses. Parses string
 * stack and tracks pair frequency with map. Skips all non bracket chars.
 */
bool Detector::hasParenPair(string &s) {
    unordered_map<char, char> CLOSED({{RPAREN, LPAREN}});

    unordered_map<char, int> freq({{RPAREN, 0}});
    unordered_map<char, int>::iterator it;

    vector<char> stack = {};
    bool isBalanced = true;

    for (char &c: s) {
        if (!isBracket(c))
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
    if (!isBalanced) {
        return false;
    }
    return freq[RPAREN] == 1;
}

/**
 * Parses file stored in Detector, inits Functions for each and stores in
 * Detector master list.
 */
void Detector::buildFunctionList() {
    int lineNo = 0;
    string line;
    ifstream inFile(this->file);
    while (getline(inFile, line)) {
        lineNo++;
        StringUtility::trimToSignature(line);
        if (skipLine(line)) {
            continue;
        }
        if (hasParenPair(line)) {
            this->masterFunctionList.emplace_back(line, lineNo);
        }
    }
    inFile.close();
}

bool Detector::skipLine(string &line) {
    return (isBlankLine(line) || isComment(line) || hasInvalidFirstToken(line));
}

/**
 * Checks the chars in the return type spot are not in the INVALID list.
 * <return type> myFunc()
 */
bool Detector::hasInvalidFirstToken(string &s) {
    string token = s.substr(0, s.find_first_of(LPAREN));
    StringUtility::trimWhitespace(token);
    return INVALID.count(token);
}

bool Detector::isBlankLine(string &s) {
    return s.length() == 0;
}

bool Detector::isComment(string &s) {
    return COMMENT_START.count((s.at(0)));
}

bool Detector::isLongMethod(Function &function) const {
    findEOFunction(function);  // assign f.end and f.blanks
    function.loc = ((function.end - function.start) - function.blanks) + 1;
    if (function.loc > LONG_METHOD_THRESHOLD) {
        function.longFunction = true;
        return true;
    }
    return false;
}

void Detector::findEOFunction(Function &function) const {
    const unordered_set<char> CURLPAIR({RCURL, LCURL});
    unordered_map<char, char> CLOSED({{RCURL, LCURL}});

    int lineNo = 0, matchesMade = 0;
    bool EOFound = false;

    vector<char> stack = {};

    string line;
    ifstream inFile(this->file);
    do {
        getline(inFile, line);
        lineNo++;
        if (lineNo < function.start) {
            continue;
        }
        if (isBlankLine(line)) {
            function.blanks++; // track blank lines for loc calc
            continue;
        }
        // for curly brace pair to EOFunction
        for (char &c: line) {
            if (!CURLPAIR.count(c))
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
            function.end = lineNo;  // store end of function
            EOFound = true;
        }
    } while (!EOFound);
    inFile.close();
}

void Detector::detectLongMethods() {
    for (auto &f: this->functionList) { isLongMethod(f); }
}

void Detector::detectLongParameterList() {
    for (auto &f: this->functionList) { isLongParameterList(f); }
}

/**
 * Number of parameters = Number of commas in function signature + 1
 */
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

/**
 * Compare stringified function's hamming ratio.
 */
void Detector::detectDuplicatedCode() {
    // find end index of each function, store to function
    for (auto &f: functionList) { findEOFunction(f); }

    // get stringified version and store to function
    for (auto &f: functionList) { stringifyFunction(f); }

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
            duplicates.insert(duplicates.end(), {f1.handle, f2.handle});
        }
    }
}

void Detector::printFunctions() {
    string bannerContent = "Functions To Analyze List";
    cout << StringUtility::banner(bannerContent);
    for (auto &f: functionList)
        cout << f << "\n";
}

/**
 * Stringify body of a function including everything between first { and last }
 * no whitespace.
 */
void Detector::stringifyFunction(Function &function) const {
    ifstream inFile(this->file);
    string ss, line;
    int lineNo = 0;

    regex r("\\s+");

    while (lineNo < function.end + 1) {
        lineNo++;
        getline(inFile, line);

        if (lineNo < function.start) { continue; }

        ss += regex_replace(line, r, "");
    }
    inFile.close();
    ss.erase(0, ss.find(LCURL));
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
