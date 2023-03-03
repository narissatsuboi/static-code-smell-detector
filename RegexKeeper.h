/**
 * @file RegexKeeper.h
 * @author Narissa Tsuboi
 */

#ifndef SNIFFY_REGEXKEEPER_H
#define SNIFFY_REGEXKEEPER_H

#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <regex>

using namespace std;

class RegexKeeper {

private:
    vector<regex> allRegexes{};
    regex simpleReturnRegex;
    regex complexReturnRegex;
    regex constructorRegex;
    regex selectLeftWSRegex;

    void buildRegexes();



public:
    RegexKeeper();
    regex simpleReg();
    regex complexReg();
    regex constructorReg();
    regex selectLeadingWSReg();

};
#endif //SNIFFY_REGEXKEEPER_H
