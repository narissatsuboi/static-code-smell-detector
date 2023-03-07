#include "Function.h"
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

/* WHITESPACE TRIM INLINE DEFINITIONS*/
// https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring

// trim from start (in place)
static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(string &s) {
    rtrim(s);
    ltrim(s);

    // trim to lst ')'
    size_t n = s.length();
    size_t idx = s.find(')');
    s.erase(n - (n - idx - 1));
}

static inline string trimToFunctionName(string &s) {
    string functionName;
    int endIdx = s.find('(');
    int startIdx = 0;
    for (int i = endIdx - 1; i >= 0; i--) {
        if (isspace(s[i])) {
            startIdx = i;
            break;
        }
    }
    functionName = s.erase(0, startIdx);
    return functionName;
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
//                printMap(freq);
                isBalanced = false;
//                return false;
            }
        } else
            stack.push_back(c);
    }
//    printMap(freq);
    //TODO need to update if a function declaration will extend multiple lines
    if (!isBalanced) {
        return false;
    }
    return freq[')'] == 1;
}

vector<Function> Detector::buildFunctionList(ifstream &inFile) {
    vector<Function> functionList;
    string line, name;
    int lineNo = 0;
    while (getline(inFile, line)) {
        lineNo++;
        trim(line);
        if (skipLine(line)) {
//            cout << "SKIPPED: " << lineNo << " " << line << endl;
            continue;
        }
        if (hasParenthesesPair(line)) {
            name = trimToFunctionName(line);
            // TODO CHECK IF EXISTS BEFORE INPUT
            functionList.emplace_back(lineNo, name, line);
//            cout << "FOUND:   " << lineNo << " " << line << endl;
        }
    }
    return functionList;
}

bool Detector::skipLine(string &line) {
    return (isBlankLine(line) || isComment(line) || hasInvalidFirstToken(line));
}

bool Detector::hasInvalidFirstToken(string &s) {
    const unordered_set<string> INVALID({"case", "class", "else", "if", "struct", "switch", "return", "throw", "while"});
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



