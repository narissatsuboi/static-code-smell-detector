/**
 * @file StringUtility.cpp
 * @author Narissa Tsuboi
 */

#include "StringUtility.h"
#include <string>
#include <algorithm>
#include <sstream>


using namespace std;

string StringUtility::sectionBreak(int l) {
    char sb[l];
    std::fill_n (sb, l, '-');
    return sb;
}

string StringUtility::banner(string &content) {
    stringstream ss;
    int BANNERLEN = 60;
    ss << sectionBreak(BANNERLEN) <<endl;
    ss << content << endl;
    ss << sectionBreak(BANNERLEN) <<endl;
    return ss.str();
}

void StringUtility::ltrimWhitespace(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void StringUtility::rtrimWhitespace(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void StringUtility::trimToSignature(string &s) {
    rtrimWhitespace(s);
    ltrimWhitespace(s);

    // trimToSignature to lst ')'
    size_t n = s.length();
    size_t idx = s.find(')');
    s.erase(n - (n - idx - 1));
}

void StringUtility::trimReturnType(string & s) {
    // myFunc(string & a, string & b)
    int endIdx = s.find('('), startIdx;

    for (int i = endIdx - 1; i >= 0; i--) {
        if (isspace(s[i])) {
            startIdx = i;
            s.erase(0, startIdx + 1);
            break;
        }
    }
}

void StringUtility::trimParameters(string &s) {
    s.erase(s.find('('));
}

void StringUtility::trimToHandle(string &s) {
    trimReturnType(s);
    trimParameters(s);
}








