/**
 * @file Jaccard.h
 * @author Narissa Tsuboi
 */

#ifndef SNIFFY_JACCARD_H
#define SNIFFY_JACCARD_H
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

class Jaccard
{
private:
    static set<string> getIntersectionSet(set <string> &s1, set<string> &s2);
    static set<string> getUnionSet(set <string> &s1, set<string> &s2);

public:

    static double getJaccardIndex(set<string> s1, set<string> s2);


};
#include "Jaccard.cpp"
#endif //SNIFFY_JACCARD_H
