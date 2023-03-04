#include "RegexKeeper.h"

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
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);

    // trim to lst ')'
    int n = s.length();
    int idx = s.find(')');
    s.erase(n - (n-idx-1));
}


/* UTILITY SIGNATURES */

void printMap(unordered_map<char, int>& m);

/* UI SIGNATURES*/

void printBanner();
void printDirections();
void printMenuOptions();
void printExitResults();
void printUsage();
string menuLoop();
bool detectAgain();

void handleExit();
bool handleSelection(string input);
bool selectedExit(string &selection);
void run(string& filepath);

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
vector<string> getSignatures(string& filepath);

////////////////////////////////////////////////////////////////////////////////

/* UTILITY DEFINITIONS */

void printMap(unordered_map<char, int> &m) {
    unordered_map<char, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        cout << "{ " << it->first << ", " << it->second << " } " << endl;
    }
}

/* UI DEFINITIONS */

void printBanner() {
    cout << "\n";
    cout << "////////////////////CODE SMELL DETECTOR ////////////////////////\n";
    cout << "\n";
}
void printDirections() {
    string directions = "DIRECTIONS\n";
    cout << directions << "\n";
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
    printBanner();
    printDirections();
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

void handleExit() {
    printExitResults();
    exit(0);
}
bool handleSelection(string input) {
    return true; // when done
}
bool selectedExit(string &selection) {
    return selection == "exit" || selection == "EXIT" || selection == "Exit";
}
void run(string& filepath) {
    bool keepGoing = true;
    string selection;
    while (keepGoing) {
        selection = menuLoop();
        handleSelection(selection);
        keepGoing = detectAgain();
    }
    handleExit();
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

vector<string> getSignatures(string &filepath) {
    vector<string> signatures = {};
    ifstream inFile(filepath);
    string line;
    int lineNo = 0;
    while(getline(inFile, line)) {
        lineNo++;

        // remove leading and trailing ws
        // trim to last )
        trim(line);

        // skip comments and ws lines
        if (skipLine(line)) {
            cout << "SKIPPED: " << lineNo << " " << line << endl;
            continue;
        }

        // find candidate line
        if (hasParenthesesPair(line)) {
            cout << "FOUND:   " << lineNo << " " << line << endl;
        }

    }
    inFile.close();
    return signatures;
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

    // store filepath from command line
    string filepath = argv[1];

    // validate file
    ifstream inFile(filepath);
    if (!inFile.is_open()) {
        cout << "\n" << "ERROR" << "\n";
        cout << "Could not open file at path: " << argv[1] << "\n";
        printUsage();
        exit(1);
    }
        inFile.close();

    // find all signatures and store in vector
    getSignatures(filepath);

    string test = "case myFunc(string& bool&) ";


    hasInvalidFirstToken(test);
//    cin.get();
}
