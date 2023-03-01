#include <limits>
#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;


/**
 * MAIN FUNCTIONS
 */

const string LM = "LONG METHOD";
const string LPL = "LONG PARAMETER METHOD";
const string DC = "DUPLICATED CODE";
const string AGAIN = "DETECT AGAIN";
const string EXIT = "exit";
const map<string, string> MENU_OPTIONS = {{"1", LM}, {"2", LPL}, {"3", DC},
                                          {"4", AGAIN}};

void printBanner() {
    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////CODE SMELL DETECTOR ////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////\n";
    cout << "\n";
}
void printDirections() {
    string directions = "DIRECTIONS\n"
                        "ANALYZE ALL METHODS\n"
                        "Eg: >> 2  + ENTER \n"
                        "OR\n"
                        "ANALYZE SPECIFIC METHODS\n"
                        "Eg: >> 1 methodname + ENTER \n"
                        "Eg: >> 2 methodname1, methodname2 + ENTER\n";

    cout << directions << "\n";
}
void printMenuOptions() {


    for (const auto& [key, value] : MENU_OPTIONS) {
        cout << ">> " << key << " : " << value << "\n";
    }
    cout << "SELECTION";
    cout << ">> ";
}

void printExitResults() {
    cout << " YOUR CODE SMELL SUMMARY IS BELOW \n";
    cout << "... ... \n";
    cout << " GOODBYE \n";
}

void handleExit() {
    printExitResults();
    exit(0);
}


bool menuLoop() {
    printBanner();
    printDirections();
    printMenuOptions();

    string selection;
    cin >> ws;
    getline(cin, selection);

    if (selection == "exit" || selection == "EXIT") {
        return false;
    }
    return true;
}

void run() {
    bool keepGoing = true;
    while(keepGoing) {
        keepGoing = menuLoop();
    }
    handleExit();
}

int main(int argc, char* argv[]) {
    run();
}
