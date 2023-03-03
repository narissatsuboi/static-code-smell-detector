/**
 * @file RegexKeeper.h
 * @author Narissa Tsuboi
 */

#include "RegexKeeper.h"

/* Private */

void RegexKeeper::buildRegexes() {
    // simpleReturnType
    string simple(R"([A-Za-z]+ [A-Za-z0-9]+\()");
    regex simpleRegex(simple);
    this->simpleReturnRegex = simpleRegex;
    this->allRegexes.push_back(simpleReturnRegex);

    // complexReturnType
    string complex(R"([^]*[A-Za-z]\>+ [A-Za-z0-9]+\([A-Za-z0-9]+& s\))");
    regex complexRegex(complex);
    this->complexReturnRegex = complexRegex;
    this->allRegexes.push_back(complexReturnRegex);

    // constructor
    string constructor(R"([A-Za-z0-9]+\([^)]*\))");
    regex constrRegex(constructor);
    this->constructorRegex = constrRegex;
    this->allRegexes.push_back(constructorRegex);

    // remove leading whitespace
    string leftWS(R"(^\s+)");
    regex leftWsRegex(leftWS);
    this->selectLeftWSRegex = leftWsRegex;

    // ToDo - remaining regexs

}

/* Public */
RegexKeeper::RegexKeeper() {
    buildRegexes();
}

regex RegexKeeper::simpleReg() {
    return this->simpleReturnRegex;
}

regex RegexKeeper::complexReg() {
    return this->complexReturnRegex;
}

regex RegexKeeper::constructorReg() {
    return this->constructorRegex;
}

regex RegexKeeper::selectLeadingWSReg() {
    return this->selectLeftWSRegex;
}
