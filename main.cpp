#include "Detector.h"
#include <algorithm>
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

const string LM = "LONG METHOD";
const string LPL = "LONG PARAMETER METHOD";
const string DC = "DUPLICATED CODE";
const string EXIT = "exit";
const string ALLONALL = "DETECTORS ON ALL METHODS";
const map<string, string> MENU_OPTIONS = {{"1", LM},
                                          {"2", LPL},
                                          {"3", DC},
                                          {"4", ALLONALL}};
string sectionBreak() {
    int n = 60;
    char sb[n];
    std::fill_n (sb, n, '-');
    return sb;
}

static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(string &s) {
    rtrim(s);
    ltrim(s);

    // trim to lst ')'
    size_t n = s.length();
    size_t idx = s.find(')');
    s.erase(n - (n - idx - 1));
}

void printStart(string &filename);

void printUsage();

string menuLoop();

bool detectAgain();

bool selectedExit(string &selection);

void printStart(string &filename) {
    stringstream ss;
    ss << sectionBreak() << endl;
    ss << "\n* WELCOME TO THE CODE SMELL DETECTOR *\n\n";
    ss << sectionBreak() << endl;

    ss << "FILE\n" << filename << endl << endl;
    ss << "INSTRUCTIONS\n";
    ss << "1. Select the code smell to detect\n";
    ss << "2. ENTER to scan all functions\n   OR \n   enter the function names + ENTER\n";
    ss << "     eg. myFunc1, myFunc2\n";
    ss << sectionBreak() << endl;
    ss << "FUNCTION LIST\n";
    ss << sectionBreak() << endl;
    cout << ss.str();
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
    cout << sectionBreak() << endl;
    cout << "SELECT SMELL\n";
    cout << sectionBreak() << endl;
    for (const auto &[key, value]: MENU_OPTIONS) {
        cout << ">> " << key << " : " << value << "\n";
    }
    string selection;
    cin >> ws;
    getline(cin, selection);
    if (selectedExit(selection)) {
        exit(0);
    }
    if (selection == "1") return LM;
    if (selection == "2") return LPL;
    if (selection == "3") return DC;
}

void printFunctionNames(vector<Function> &functions) {
    int i = 1;
    for (const auto& function: functions) {
        cout << i << " " << function.handle << endl;
        i++;
    }
}

vector<string> parseTokens(string& input) {
    auto const reg = std::regex{R"(\s+|,\s+)"};
    auto tokens = vector<std::string>(
            sregex_token_iterator{begin(input), end(input), reg, -1},
            sregex_token_iterator{}
    );
    return tokens;
}

string selectFunctions(string& key) {
    cout << sectionBreak() << endl;
    cout << key << " ANALYSIS" << endl;
    cout << sectionBreak() << endl;
    if (key == LM || key == LPL) {
        cout << "To analyze ALL functions, press 0 + ENTER" << endl;
        cout << "To analyze specific methods, enter their number separated by\ncomma and press ENTER" << endl;
        cout << "Example: 1, 2, 4 + ENTER" << endl;
        string selections;
        cin >> ws;
        getline(cin, selections);
        vector<string> functionsToSmell = parseTokens(selections);

        if (key == LM) {
            cout << "CALL LM here" << endl;
        }
        else if (key == LPL) {
            cout << "CALL LPL here" << endl;
        }
    } else if (key == DC) {
        cout << "CALL DC HERE" << endl;
    }
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
    inFile.close();
    Detector detect = Detector(filepath);
//    printStart(filepath);
//    printFunctionNames(detect.functionList);
//    string selection = menuLoop();
//    selectFunctions(selection);
    detect.isLongMethod(detect.functionList[0]);
}
