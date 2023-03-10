/**
 * @file Function.cpp
 * @author Narissa Tsuboi
 */

#include "Function.h"
#include "StringUtility.h"
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

Function::Function() = default;

Function::Function(string &fullSignature, int &startLine) {
    this->signature = fullSignature;
    this->start = startLine;
    format();
}

void Function::format() {
    string tempHandle = this->signature;
    StringUtility::trimToHandle(tempHandle);
    this->handle = tempHandle;
}

ostream &operator<<(ostream &os, const Function &func) {
    os << StringUtility::sectionBreak(30) << endl;
    os << func.signature << endl;
    os << StringUtility::sectionBreak(30) << endl;
    os << "range:  " << func.start << ", " << func.end << endl;
    os << "handle: " << func.handle << endl;
    os << "LF    : " << func.longFunction << endl;
    os << "loc:    " << func.loc << endl;
    os << "LPL   : " << func.longFunction << endl;
    os << "params: " << func.paramCount << endl;
    os << "DC    : " << func.dupCode << endl;

    return os;
}


