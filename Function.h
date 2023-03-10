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
    int start{};
    int end{};
    int loc{};
    bool longmethod{};
    int paramCount{};
    bool longparams{};
    bool dupcode{};

    Function();

    Function(string &fullSignature, int &startLine);

    void format();

    bool dupCode();


    friend ostream &operator<<(ostream &os, const Function &func);
};

#include "Function.cpp"

#endif //SNIFFY_FUNCTION_H
