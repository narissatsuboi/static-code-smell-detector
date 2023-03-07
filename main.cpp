#include "RegexKeeper.h"
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

using namespace std;

// HEADER /////////////////////////////////////////////////////////////////////

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
    size_t  n = s.length();
    size_t  idx = s.find(')');
    s.erase(n - (n-idx-1));
}

static inline string trimToFunctionName(string &s) {
    string functionName;
    int endIdx = s.find('(');
    int startIdx = 0;
    for (int i = endIdx - 1; i>=0; i--) {
        if (isspace(s[i])) {
            startIdx = i;
            break;
        }
    }
    functionName = s.erase(0, startIdx);
    return functionName;
}

/* UTILITY SIGNATURES */

void printMap(unordered_map<char, int>& m);

/* UI SIGNATURES*/

void printStart(string &filename);
void printDirections();
void printFunctionNames(map<string, Function> &functions);
void printMenuOptions();
void printExitResults();
void printUsage();
string menuLoop();
bool detectAgain();


bool selectedExit(string &selection);

const string LM = "LONG METHOD";
const string LPL = "LONG PARAMETER METHOD";
const string DC = "DUPLICATED CODE";
const string EXIT = "exit";
const string ALLONALL = "DETECTORS ON ALL METHODS";
const map<string, string> MENU_OPTIONS = {{"1", LM}, {"2", LPL}, {"3", DC}, {"4", ALLONALL}};

/* DETECTOR SIGNATURES*/

bool skipLine(string&s);
bool hasInvalidFirstToken(string&s);
bool hasParenthesesPair(string&s);
bool isBlankLine(string&s);
bool isComment(string&s);
bool isDelimiter(char&c);
vector<Function> buildFunctionList(ifstream &inFile);

////////////////////////////////////////////////////////////////////////////////

/* UTILITY DEFINITIONS */

void printMap(unordered_map<char, int> &m) {
    unordered_map<char, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        cout << "{ " << it->first << ", " << it->second << " } " << endl;
    }
}

/* UI DEFINITIONS */

void printStart(string &filename) {
    stringstream ss;
    ss << "\n* WELCOME TO THE CODE SMELL DETECTOR *\n\n";
    ss << "FILE\n" << filename << endl << endl;
    ss << "INSTRUCTIONS\n";
    ss << "1. Select the code smell to detect\n";
    ss << "2. ENTER to scan all functions\n   OR \n   enter the function names + ENTER\n";
    ss << "     eg. myFunc1, myFunc2\n";
    cout << ss.str();
}

void printFunctionNames(vector<Function> &functions) {
    stringstream ss;
    cout << "\nFUNCTION LIST\n";

    for (auto function : functions) {
        cout << function.handle << endl;
    }
}

void printMenuOptions() {
    for (const auto &[key, value]: MENU_OPTIONS) {
        cout << ">> " << key << " : " << value << "\n";
    }
}
void printExitResults() {
    cout << " YOUR CODE SMELL SUMMARY IS BELOW \n";
    cout << "... ... \n";
    cout << " GOODBYE \n";
}
void printUsage() {
    string compileCommand = "$ g++ main.cpp -o smelldetector";
    string runCommand = "$ ./smelldetector pathToFile";
    string localExample = "$ smelldetector stinkyFile.cpp";
    string relativeExample = "$ smelldetector myFiles/stinkyFile.cpp";
    string absoluteExample = "$ smelldetector C:Desktop/myProject/myFiles/stinkyFile.cpp";

    stringstream ss;
    ss << "\n" << "USAGE" << "\n";
    ss << "compile: " << compileCommand << "\n";
    ss << "run:     " << runCommand << "\n";
    ss << "eg:      " << localExample << "\n";
    ss << "eg:      " << relativeExample << "\n";
    ss << "eg:      " << relativeExample << "\n";
    ss << "eg:      " << absoluteExample << "\n";
    cout << ss.str() << "\n";
}
string menuLoop() {
    printMenuOptions();
    string selection;
    cin >> ws;
    getline(cin, selection);
    cout << selection;

    if (selectedExit(selection)) {
        exit(0);
    }
    return selection;
}
bool detectAgain() {
    stringstream ss;
    ss << "\n";
    ss << "Would you like to detect again?" << "\n";
    ss << "Yes or Exit?   ";
    cout << ss.str();
    string selection;
    cin >> ws;
    getline(cin, selection);
    return !(selectedExit(selection));
}

bool selectedExit(string &selection) {
    return selection == "exit" || selection == "EXIT" || selection == "Exit";
}

/* DETECTOR DEFINIONS */

bool hasParenthesesPair(string &s) {
    unordered_map<char, char> CLOSED({{')', '('}, {'}', '{'}, {']', '['}});
    unordered_map<char, int> freq ({{')', 0}, {'}', 0}, {']', 0}});
    unordered_map<char, int>::iterator it;
    vector<char> stack = {};
    bool isBalanced = true;
    for (char &c : s) {
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

vector<Function> buildFunctionList(ifstream &inFile) {
    vector<Function> functionList;
    string line, name;
    int lineNo = 0;
    while(getline(inFile, line)) {
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

bool skipLine(string&line) {
    return (isBlankLine(line) || isComment(line) || hasInvalidFirstToken(line));
}

bool hasInvalidFirstToken(string&s) {
    const unordered_set<string> INVALID ({ "case", "class", "else", "if", "struct","switch", "return", "throw","while"});
    string token = s.substr(0, s.find_first_of(' '));
    return INVALID.count(token);
}

bool isBlankLine(string&s) {
    return s.length() == 0;
};

bool isComment(string&s) {
    unordered_set<char> SKIP({'#', '/', '*'});
    return SKIP.count((s.at(0)));
}

bool isDelimiter(char &c) {
    const unordered_set<char> DELIMS ({ ')', '(', '}', '{', ']', '['});
    return DELIMS.count(c);
}



// MAIN ////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    // usage
    if (argc < 2) {
        printUsage();
        exit(1);
    }

    string filepath = argv[1];
    ifstream inFile(filepath);
    if (!inFile.is_open()) {
        cout << "\n" << "ERROR" << "\n";
        cout << "Could not open file at path: " << argv[1] << "\n";
        printUsage();
        exit(1);
    }

    printStart(filepath);
    vector<Function> handles = buildFunctionList(inFile);
    printFunctionNames(handles);

    string selection = menuLoop();
    string s = "int myFunc()";

    // find all signatures
    inFile.close();
    cin.get();
}
