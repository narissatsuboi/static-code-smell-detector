/**
 * @file Detector.h
 * @author Narissa Tsuboi
 */

#include "Function.h"
#include <vector>
#include <set>
#ifndef SNIFFY_DETECTOR_H
#define SNIFFY_DETECTOR_H

class Detector
{
public:
    explicit Detector(string &filepath);

    vector<Function> masterFunctionList;
    vector<Function> functionList;
    string file;

    vector<string> duplicates;

    static bool skipLine(string &line);

    static bool hasInvalidFirstToken(string &s);

    static bool hasParenPair(string &s);

    static bool isBlankLine(string &s);

    static bool isComment(string &s);

    static bool isBracket(char &c);

    void buildFunctionList();

    void findEOFunction(Function &function) const;

    void detectLongMethods();

    bool isLongMethod(Function &function) const;

    void detectLongParameterList();

    static void isLongParameterList(Function & function);

    void detectDuplicatedCode();

    void isDuplicatedCode(Function & f1, Function & f2);

    static double hammingRatio(string& s1, string&s2);

    void stringifyFunction(Function &function) const;

};

#include "Detector.cpp"

#endif //SNIFFY_DETECTOR_H
