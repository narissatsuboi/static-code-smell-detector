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
    os << "loc:    " << func.loc << endl;
    os << "params: " << func.paramCount << endl;
    return os;
}


