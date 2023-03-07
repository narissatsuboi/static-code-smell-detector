#include "Function.h"
#include <vector>

#ifndef SNIFFY_DETECTOR_H
#define SNIFFY_DETECTOR_H

class Detector
{
public:
    explicit Detector(string &filepath);
    vector<Function> functionList;
    string file;

    bool skipLine(string &s);

    static bool hasInvalidFirstToken(string &s);

    bool hasParenthesesPair(string &s);

    static bool isBlankLine(string &s);

    static bool isComment(string &s);

    bool isDelimiter(char &c);

    void buildFunctionList();

    bool isLongMethod(Function &function);

};

#endif //SNIFFY_DETECTOR_H
