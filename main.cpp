/**
 * @file main.cpp
 * @author Narissa Tsuboi
 */

#include "StringUtility.h"
#include "Detector.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include <set>

using namespace std;

const int BREAKLEN = 60;
const string LF = "LONG FUNCTION";
const string LPL = "LONG PARAMETER METHOD";
const string DC = "DUPLICATED CODE";
const string INV = "INVALD";
const string EXIT = "exit";
const string ALLONALL = "DETECTORS ON ALL METHODS";
map<string, string> MENU_OPTIONS = {{"1", LF},
                                          {"2", LPL},
                                          {"3", DC},
                                          {"4", ALLONALL}};

static inline void printUsage() {
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

static inline void printStart(string &filename) {
    string welcomeBannerContent = "* WELCOME TO THE CODE SMELL DETECTOR *";
    string listBannerContent = "FUNCTION LIST";
    stringstream ss;
    ss << StringUtility::banner(welcomeBannerContent);
    ss << "FILE\n" << filename << endl << endl;
    ss << "INSTRUCTIONS\n";
    ss << "1. Select the code smell to detect\n";
    ss << "2. ENTER to scan all functions\n   OR \n   enter the function names + ENTER\n";
    ss << "     eg. myFunc1, myFunc2\n";
    ss << StringUtility::banner(listBannerContent);
    cout << ss.str();
}

string menuLoop();

void printFunctionNames(vector<Function> &functions);

void handleSelection(string &key, Detector &detect);

vector<string> parseTokens(string &input);

vector<string> getFunctionNumbers(int numFunctions);

string LMResults(Detector &d);

void printResults(string &key, Detector &detect);

bool detectAgain();

string menuLoop() {
    string bannerContent = "SELECT SMELL";
    cout << StringUtility::banner(bannerContent);
    for (const auto &[key, value]: MENU_OPTIONS) {
        cout << ">> " << key << " : " << value << "\n";
    }
    bool validSelection = true;
    string selection;
    do {
        cin >> ws;
        getline(cin, selection);
        if (MENU_OPTIONS.count(selection)) {
            return MENU_OPTIONS[selection];
        } else {
            cout << "*** Invalid selection, please try again. ***" << endl;
            validSelection = false;
        }
    } while(!validSelection);
    return selection;
}

void printFunctionNames(vector<Function> &functions) {
    int i = 1;
    // toDo
    for (const auto &function: functions) {
        cout << i << " " << function.handle << endl;
        i++;
    }
}

void handleSelection(string &key, Detector &detect) {
    int totalNumFunctions = detect.functionList.size();
    string bannerContent = key + " ANALYSIS";
    cout << StringUtility::banner(bannerContent);
    if (key == DC) {
        cout << "CALL DC HERE" << endl;
        return;
    }
    vector<string> functionNums = getFunctionNumbers(totalNumFunctions);

    if (functionNums.size() == 1 && functionNums[0] == "0") {
        detect.functions = detect.functionList;
    } else {
        for (const auto &functionNum: functionNums) {
            int functNum = stoi(functionNum);
            Function &f = detect.functionList[functNum - 1];
            detect.functions.push_back(f);
        }
    }

    if (key == LF) {
        detect.detectLongMethods();
    }
}

vector<string> parseTokens(string &input) {
    auto const reg = std::regex{R"(\s+|,\s+)"};
    auto tokens = vector<std::string>(
            sregex_token_iterator{begin(input), end(input), reg, -1},
            sregex_token_iterator{}
    );
    return tokens;
}

vector<string> getFunctionNumbers(int numFunctions) {
    cout << "To analyze ALL functions, press 0 + ENTER" << endl;
    cout << "To analyze specific methods, enter their number separated by\ncomma and press ENTER" << endl;
    cout << "Example: 1, 2, 4 + ENTER" << endl;
    string selections;
    bool validFunction = true;
    vector<string> functionNums;
    do {
        cin >> ws;
        getline(cin, selections);
        functionNums = parseTokens(selections);
        for (auto &fn: functionNums) {
            if (stoi(fn) < 1 || stoi(fn) > numFunctions) {
                validFunction = false;
                break;
            } else {
                validFunction = true;
            }
        }
        cout << "*** Invalid function number, please try again. ***" << endl;
    } while(!validFunction);

    return functionNums;
}

string LMResults(Detector &d) {
    int lmCount = 0;
    stringstream ss;
    for (auto &f: d.functions) {
        if (f.longmethod) {
            lmCount++;
            ss << f.signature << " is a Long Function. ";
            ss << "It contains " << f.loc << " lines. ";
        }
    }
    if (lmCount == 0) {
        ss << "No function is a Long Function." << endl;
    }

    return ss.str();
}

void printResults(string &key, Detector &detect) {
    string bannerContent = "RESULTS";
    stringstream ss;
    ss << StringUtility::banner(bannerContent);
    if (key == LF) {
        ss << LMResults(detect);
    } else if (key == LPL) {
        ss << LMResults(detect);
    } else if (key == DC) {
        ss << LMResults(detect);
    }
    cout << ss.str() << endl;
}


void printExit() {
    stringstream ss;
    string bannerContent = "GOODBYE!";
    ss << endl;
    ss << StringUtility::banner(bannerContent);
    cout << ss.str();
}

bool detectAgain() {
    unordered_set<string> exit = {{"No", "NO", "no", "nO", "n", "N"}};
    stringstream ss;
    ss << "\n";
    ss << "Would you like to detect again?" << "\n";
    ss << "Enter any key to continue + Enter OR \"No\" + Enter to exit.\n";
    cout << ss.str();
    string selection;
    cin >> ws;
    getline(cin, selection);
    if (exit.count(selection)) {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    // usage
    if (argc < 2) {
        printUsage();
        exit(1);
    }

    bool keepSmelling = true;
    while(keepSmelling) {
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
        printStart(filepath);
        printFunctionNames(detect.functionList);
        string selection = menuLoop();
        handleSelection(selection, detect);
        printResults(selection, detect);
        if(!detectAgain()) {
            keepSmelling = false;
        }
    }

    printExit();
    exit(0);
}
