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

    static bool skipLine(string &line);

    static bool hasInvalidFirstToken(string &s);

    static bool hasParenthesesPair(string &s);

    static bool isBlankLine(string &s);

    static bool isComment(string &s);

    static bool isDelimiter(char &c);

    void buildFunctionList();

    void findEOFunction(Function &function) const;

    void detectLongMethods();

    bool isLongMethod(Function &function) const;

    void detectLongParameterList();

    static void isLongParameterList(Function & function);


};

#include "Detector.cpp"

#endif //SNIFFY_DETECTOR_H
