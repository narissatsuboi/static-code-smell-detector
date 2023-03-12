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
    os << StringUtility::sectionBreak(45) << "\n";
    os << func.signature << "\n";
    os << StringUtility::sectionBreak(45) << "\n";
    os << "range:  " << func.start << ", " << func.end << "\n";
    os << "handle: " << func.handle << "\n";
    os << "LF    : " << func.longFunction << "\n";
    os << "loc:    " << func.loc << "\n";
    os << "LPL   : " << func.longFunction << "\n";
    os << "params: " << func.paramCount << "\n";
    os << "str   : " << func.stringified << "\n";
    os << "chco  : " << func.charCount << "\n";


    return os;
}


