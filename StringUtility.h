/**
 * @file StringUtility.h
 * @author Narissa Tsuboi
 */
#ifndef SNIFFY_STRINGUTILITY_H
#define SNIFFY_STRINGUTILITY_H
#include <string>

using namespace std;

class StringUtility
{

private:
    static void ltrimWhitespace(string &s);

    static void rtrimWhitespace(string &s);

    static void trimReturnType(string & s);

    static void trimParameters(string& s);

public:

    static string banner(string & content);

    static string sectionBreak(int l);

    static void trimToSignature(string &s);

    static void trimToHandle(string& s);

};

#include "StringUtility.cpp"
#endif //SNIFFY_STRINGUTILITY_H
