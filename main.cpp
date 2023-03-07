#include "Detector.h"
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
void printStart(string &filename);

void printFunctionNames(map<string, Function> &functions);

void printMenuOptions();

void printUsage();

string menuLoop();

bool detectAgain();

bool selectedExit(string &selection);

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

    for (auto function: functions) {
        cout << function.handle << endl;
    }
}

void printMenuOptions() {
    for (const auto &[key, value]: MENU_OPTIONS) {
        cout << ">> " << key << " : " << value << "\n";
    }
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
    vector<Function> handles = Detector::buildFunctionList(inFile);
    printFunctionNames(handles);

    string selection = menuLoop();
    string s = "int myFunc()";

    // find all signatures
    inFile.close();
    cin.get();
}
