/**
 * @file main.cpp
 * @author Narissa Tsuboi
 */

#include "StringUtility.h"
#include "Detector.h"
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
map<string, string> MENU_OPTIONS = {{"1", LF},
                                    {"2", LPL},
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

bool areValidFunctionChoices(vector<string> &functionNumbers, int &maxChoice);

bool detectAgain();

string DCResults(Detector &d);

void handleSelection(string &key, Detector &detect);

bool isValidInteger(string &n);

vector<string> getFunctionChoices(int maxChoice);

string menuLoop();

vector<string> parseTokens(string &input);

void printFunctionNames(vector<Function> &functions);

void printExit();

void printResults(string &key, Detector &detect);

string LPLResults(Detector &d);

string LMResults(Detector &d);

/* DEFINITIONS */

string menuLoop() {
    string bannerContent = "SELECT SMELL";
    cout << StringUtility::banner(bannerContent);
    for (const auto &[key, value]: MENU_OPTIONS) {
        cout << ">> " << key << " : " << value << "\n";
    }
    bool validSelection = false;
    string selection;
    do {
        cout << StringUtility::banner(bannerContent);
        for (const auto &[key, value]: MENU_OPTIONS) {
            cout << ">> " << key << " : " << value << "\n";
        }
        cin >> ws;
        getline(cin, selection);
        if (isValidInteger(selection) && MENU_OPTIONS.count(selection)) {
            validSelection = true;
        } else {
            cout << "(!) Invalid input." << "\n";
            validSelection = false;
        }
    } while (!validSelection);

    return MENU_OPTIONS[selection];
}

void printFunctionNames(vector<Function> &functions) {
    int i = 1;
    // toDo
    for (const auto &function: functions) {
        cout << i << ". " << function.handle << "\n";
        i++;
    }
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
        ss << DCResults(detect);
    }
    cout << ss.str() << "\n";
}

string LMResults(Detector &d) {
    int lmCount = 0;
    stringstream ss;
    for (auto &f: d.functionList) {
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
    for (auto &f: d.functionList) {
        if (f.longParam) {
            lplcount++;
            ss << f.handle << " has a Long Parameter List. Its parameter list contains ";
            ss << f.paramCount << " parameters." << "\n";
        }
    }
    if (lplcount == 0) {
        ss << "No function has a Long Parameter List" << "\n";
    }
    return ss.str();
}

string DCResults(Detector &d) {
    stringstream ss;
    if (d.dups.empty()) {
        ss << "No functions are duplicated" << "\n";
    } else {
        int j;
        for (auto i = 0; i < d.dups.size() - 1; i++) {
            j = i + 1;
            ss << d.dups[i] << " and " << d.dups[j] << " are duplicated\n";
            i++;
        }
    }
    return ss.str();
}

void printExit() {
    stringstream ss;
    string bannerContent = "GOODBYE!";
    ss << "\n";
    ss << StringUtility::banner(bannerContent);
    cout << ss.str();
}

bool detectAgain() {
    stringstream ss;
    ss << "\n";
    ss << "Would you like to detect again?" << "\n";
    ss << "\"Y\" or \"y\" to detect again or any other key to exit\n";
    cout << ss.str();
    string selection;
    cin >> ws;
    getline(cin, selection);
    return selection == "Y" || selection == "y";
}

void handleSelection(string &key, Detector &detect) {
    if (key == QUIT) {  // exit on QUIT from user
        printExit();
        exit(0);
    }

    // analysis start
    string bannerContent = key + " ANALYSIS";
    cout << StringUtility::banner(bannerContent);

    // analyze all functionList if duplicate code or user selected all functionList
    if (key != DC) {
        vector<string> selectedFunctionIdxs = getFunctionChoices(detect.masterFunctionList.size());
        if (selectedFunctionIdxs[0] == "0") {
            detect.functionList = detect.masterFunctionList;
        } else {
            for (const auto &num: selectedFunctionIdxs) {
                detect.functionList.push_back(detect.masterFunctionList[stoi(num) - 1]);
            }
        }
    }

    // perform analysis
    if (key == LF) {
        detect.detectLongMethods();
    } else if (key == LPL) {
        detect.detectLongParameterList();
    } else if (key == DC) {
        detect.functionList = detect.masterFunctionList;
        detect.detectDuplicatedCode();
    }
}

vector<string> parseTokens(string &input) {
    auto const reg = std::regex{R"(\s+| \s+)"};
    auto tokens = vector<std::string>(
            sregex_token_iterator{begin(input), end(input), reg, -1},
            sregex_token_iterator{}
    );
    return tokens;
}

bool isValidInteger(string &n) {
    try {
        stoi(n);
    } catch (invalid_argument &e) {
        return false;
    }
    return true;
}

bool areValidFunctionChoices(vector<string> &functionNumbers, int &maxChoice) {
    for (auto &fn: functionNumbers) {
        if (!isValidInteger(fn) || stoi(fn) < 0 || stoi(fn) > maxChoice) {
            cout << "(!) Invalid input\n";
            return false;
        }
    }
    return true;
}

vector<string> getFunctionChoices(int maxChoice) {

    string selections;
    vector<string> functionNums;
    do {
        cout << "To analyze ALL functions, enter 0, OR" << "\n";
        cout << "enter function numbers separated by a space" << "\n";
        cout << "Ex. 1 2 4 11" << "\n";
        cin >> ws;
        getline(cin, selections);
        functionNums = parseTokens(selections);
    } while (!areValidFunctionChoices(functionNums, maxChoice));
    return functionNums;
}

int main(int argc, char *argv[]) {
    // usage
    if (argc < 2) {
        printUsage();
        exit(1);
    }

    bool keepSmelling = true;
    while (keepSmelling) {
        string filepath = argv[1];
        ifstream inFile(filepath);
        // validate filepath
        if (!inFile.is_open()) {
            cout << "\n" << "ERROR" << "\n";
            cout << "Could not open file at path: " << argv[1] << "\n";
            printUsage();
            exit(1);
        }
        inFile.close();

        // init detector and build function list
        Detector detect = Detector(filepath);
        printStart(filepath);
        printFunctionNames(detect.masterFunctionList);

        // handle selection of code smell type
        string selection = menuLoop();
        handleSelection(selection, detect);

        // log code smell results to screen
        printResults(selection, detect);
        keepSmelling = detectAgain();
    }

    printExit();
    exit(0);
}
