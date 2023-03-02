#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

/* Signatures */

void printBanner();

void printDirections();

void printMenuOptions();

void printExitResults();

void printUsage();

void handleExit();

string menuLoop();

bool handleSelection(string input);

bool detectAgain();

bool selectedExit(string &selection);

void run(string& filepath);

const string LM = "LONG METHOD";
const string LPL = "LONG PARAMETER METHOD";
const string DC = "DUPLICATED CODE";
const string EXIT = "exit";
const string ALLONALL = "DETECTORS ON ALL METHODS";
const map<string, string> MENU_OPTIONS = {{"1", LM},
                                          {"2", LPL},
                                          {"3", DC},
                                          {"4", ALLONALL}};
/* Driver Methods */

void printBanner() {
    cout << "\n";
    cout << "////////////////////CODE SMELL DETECTOR ////////////////////////\n";
    cout << "\n";
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

bool handleSelection(string input) {
    return true; // when done
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

void printExitResults() {
    cout << " YOUR CODE SMELL SUMMARY IS BELOW \n";
    cout << "... ... \n";
    cout << " GOODBYE \n";
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

namespace Detect {
    void readFile(string& filepath);

    void readFile(string &filepath) {
        ifstream inFile(filepath);
        string line;
        while(getline(inFile, line)) {
            cout << line << "\n";
        }
        inFile.close();
    }
}

int main(int argc, char *argv[]) {
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
    Detect::readFile(filepath);
//    inFile.close();
//    run(filepath);
}
