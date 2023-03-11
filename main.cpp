/**
 * @file main.cpp
 * @author Narissa Tsuboi
 */

#include "StringUtility.h"
#include "Detector.h"
#include "Jaccard.h"
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

/* GLOBALS */
const string LF = "LONG METHOD/FUNCTION DETECTION";
const string LPL = "LONG PARAMETER LIST DETECTION";
const string DC = "DUPLICATED CODE DETECTION";
const string QUIT = "QUIT";
map<string, string> MENU_OPTIONS = {{"1", LF}, {"2", LPL},
                                    {"3", DC},
                                          {"4", QUIT}};

/* INLINE FUNCTIONS */

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
    ss << "FILE\n" << filename << "\n" << "\n";
    ss << StringUtility::banner(listBannerContent);
    cout << ss.str();
}

/* DECLARATIONS */

string menuLoop();

void printFunctionNames(vector<Function> &functions);

void handleSelection(string &key, Detector &detect);

vector<string> parseTokens(string &input);

vector<string> getFunctionNumbers(int numFunctions);

string LMResults(Detector &d);

string LPLResults(Detector &d);

void printResults(string &key, Detector &detect);

bool detectAgain();

void printExit();

/* DEFINITIONS */

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
            cout << "*** Invalid selection, please try again. ***" << "\n";
            validSelection = false;
        }
    } while(!validSelection);
    return selection;
}

void printFunctionNames(vector<Function> &functions) {
    int i = 1;
    // toDo
    for (const auto &function: functions) {
        cout << i << ". " << function.handle << "\n";
        i++;
    }
}

void handleSelection(string &key, Detector &detect) {
    if (key == QUIT) {  // exit on QUIT from user
        printExit();
        exit(0);
    }

    // analysis start
    string bannerContent = key + " ANALYSIS";
    cout << StringUtility::banner(bannerContent);

    // fill Detector's function list based on user input
    int totalNumFunctions = detect.masterFunctionList.size();
    vector<string> functionNums = getFunctionNumbers(totalNumFunctions);

    // analyze all functionsToAnalyze if duplicate code or user selected all functionsToAnalyze
    if (key == "DC" || (functionNums.size() == 1 && functionNums[0] == "0")) {
        detect.functionsToAnalyze = detect.masterFunctionList;
    } else { // custom pick from master list
        for (const auto &functionNum: functionNums) {
            int functNum = stoi(functionNum);
            Function &f = detect.masterFunctionList[functNum - 1];
            detect.functionsToAnalyze.push_back(f);
        }
    }

    // perform analysis
    if (key == LF) {
        detect.detectLongMethods();
    }

    if (key == LPL) {
        detect.detectLongParameterList();
    }

    if (key == DC) {
        cout << "CALL DC HERE" << "\n";
        return;
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
    cout << "To analyze ALL functionsToAnalyze, press 0 + ENTER" << "\n";
    cout << "To analyze specific methods, enter their number separated by\ncomma and press ENTER" << "\n";
    cout << "Example: 1, 2, 4 + ENTER" << "\n";
    string selections;
    bool validFunction = true;
    vector<string> functionNums;
    do {
        cin >> ws;
        getline(cin, selections);
        functionNums = parseTokens(selections);
        for (auto &fn: functionNums) {
            if (stoi(fn) < 0 || stoi(fn) > numFunctions) {
                validFunction = false;
                cout << "*** Invalid function number, please try again. ***" << "\n";
                break;
            } else {
                validFunction = true;
            }
        }
    } while(!validFunction);

    return functionNums;
}

string LMResults(Detector &d) {
    int lmCount = 0;
    stringstream ss;
    for (auto &f: d.functionsToAnalyze) {
        if (f.longFunction) {
            lmCount++;
            ss << f.handle << " is a Long Function. ";
            ss << "It contains " << f.loc << " lines. " << "\n";
        }
    }
    if (lmCount == 0) {
        ss << "No function is a Long Function." << "\n";
    }
    return ss.str();
}
string LPLResults(Detector &d) {
    int lplcount = 0;
    stringstream ss;
    for (auto &f: d.functionsToAnalyze) {
        if (f.longParam) {
            lplcount++;
            ss << f.handle << " has a Long Parameter List. Its paramter list contains ";
            ss << f.paramCount << " parameters." << "\n";
        }
    }
    if (lplcount == 0) {
        ss << "No function has a Long Parameter List" << "\n";
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
        ss << LPLResults(detect);
    } else if (key == DC) {
        ss << LMResults(detect);
    }
    cout << ss.str() << "\n";
}

void printExit() {
    stringstream ss;
    string bannerContent = "GOODBYE!";
    ss << "\n";
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
        printFunctionNames(detect.masterFunctionList);

        string selection = menuLoop();
        handleSelection(selection, detect);
        printResults(selection, detect);
        if(!detectAgain()) {
            keepSmelling = false;
        }
        keepSmelling = false;
    }

    printExit();
    exit(0);
}
