
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

const string LM = "LONG METHOD";
const string LPL = "LONG PARAMETER METHOD";
const string DC = "DUPLICATED CODE";
const string AGAIN = "DETECT AGAIN";
const string EXIT = "EXIT";


void printTitle();
void menuLoop();
bool selectionHandler(string& s);

void printTitle() {
    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////CODE SMELL DETECTOR ////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////\n";
    cout << "\n";
}

void menuLoop() {

    string directions = "DIRECTIONS\n"
                        "ANALYZE ALL METHODS\n"
                        "Eg: >> 2  + ENTER \n"
                        "OR\n"
                        "ANALYZE SPECIFIC METHODS\n"
                        "Eg: >> 1 methodname + ENTER \n"
                        "Eg: >> 2 methodname1, methodname2 + ENTER\n";

    map<string, string> choices{
            {"1", LM},
            {"2", LPL},
            {"3", DC},
            {"4", AGAIN},
            {"5", EXIT}
    };
    cout << directions << "\n";
    for (const auto& [key, value] : choices) {
        cout << ">> " << key << " : " << value << "\n";
    }

    string selection;
    cout << "YOUR INPUT\n";
    cout << ">>";
    cin >> selection;

    selectionHandler(choices[selection]);
}

bool selectionHandler(string &codeSmell) {


    return false;
}

int main() {
    printTitle();
    menuLoop();
}
