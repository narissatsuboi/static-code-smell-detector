/**
 * @file Detector.h
 * @author Narissa Tsuboi
 */

#include "Function.h"
#include <vector>

#ifndef SNIFFY_DETECTOR_H
#define SNIFFY_DETECTOR_H

class Detector
{
public:
    explicit Detector(string &filepath);

    vector<Function> masterFunctionList;
    vector<Function> functionsToAnalyze;
    string file;

    bool skipLine(string &line);

    static bool hasInvalidFirstToken(string &s);

    bool hasParenthesesPair(string &s);

    static bool isBlankLine(string &s);

    static bool isComment(string &s);

    bool isDelimiter(char &c);

    void buildFunctionList();

    void detectLongMethods();

    bool isLongMethod(Function &function) const;

    void detectLongParameterList();

    void isLongParameterList(Function & function);


};

#include "Detector.cpp"

#endif //SNIFFY_DETECTOR_H
