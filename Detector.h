#include "Function.h"

#ifndef SNIFFY_DETECTOR_H
#define SNIFFY_DETECTOR_H

class Detector
{
public:
    static bool skipLine(string &s);

    static bool hasInvalidFirstToken(string &s);

    static bool hasParenthesesPair(string &s);

    static bool isBlankLine(string &s);

    static bool isComment(string &s);

    static bool isDelimiter(char &c);

    static vector<Function> buildFunctionList(ifstream &inFile);
};

#endif //SNIFFY_DETECTOR_H
