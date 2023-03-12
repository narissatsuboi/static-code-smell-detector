/**
 * @file Function.cpp
 * @author Narissa Tsuboi
 */

#include "Function.h"
#include "StringUtility.h"
#include <iostream>

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


