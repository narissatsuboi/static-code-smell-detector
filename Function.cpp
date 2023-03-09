/**
 * @file Function.cpp
 * @author Narissa Tsuboi
 */

#include "Function.h"
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

static inline string sectionBreak() {
    int n = 30;
    char sb[n];
    std::fill_n (sb, n, '-');
    return sb;
}

Function::Function() = default;

Function::Function(int &startLine, string &name, string &fullSignature) {
    this->handle = name;
    this->start = startLine;
}

ostream& operator<<(ostream &os, const Function &func) {
    os << sectionBreak() << endl;
    os << func.handle << endl;
    os << sectionBreak() << endl;
    os << "loc:    " << func.loc << endl;
    os << "params: " << func.paramCount << endl;
    return os;
}
