/**
 * @file Function.h
 * @author Narissa Tsuboi
 */

#ifndef SNIFFY_FUNCTION_H
#define SNIFFY_FUNCTION_H

#include <string>

using namespace std;

class Function
{
private:

public:
    string signature;
    string handle;
    string params;
    int start = 0;
    int end = 0;
    int blanks = 0;
    int loc = 0;
    bool longFunction = false;
    size_t paramCount = 0;
    bool longParam = false;
    string stringified;
    size_t charCount = 0;

    Function();

    Function(string &fullSignature, int &startLine);

    void format();

    friend ostream &operator<<(ostream &os, const Function &func);
};

#include "Function.cpp"

#endif //SNIFFY_FUNCTION_H
