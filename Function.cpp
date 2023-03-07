#include "Function.h"


#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include <set>


using namespace std;

const int LONG_METHOD_THRESHOLD = 15;

const int LONG_PARAM_THRESHOLD = 3;


Function::Function() = default;

Function::Function(int &startLine, string &name, string &fullSignature) {
    this->handle = name;
    this->start = startLine;
}

bool Function::isLongMethod() const {
    return this->loc > LONG_METHOD_THRESHOLD;
}

bool Function::isLongParams() const {
    return this->paramCount > LONG_METHOD_THRESHOLD;
}

bool Function::isDupCode() {
    return false;
}