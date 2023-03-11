/**
 * @file Jaccard.cpp
 * @author Narissa Tsuboi
 * @references
 * https://studymachinelearning.com/jaccard-similarity-text-similarity-metric-in-nlp/
 * https://www.geeksforgeeks.org/find-the-jaccard-index-and-jaccard-distance-between-the-two-given-sets/
 */

using namespace std;
#include <bits/stdc++.h>

#include "Jaccard.h"

set<string> Jaccard::getIntersectionSet(set <string> &s1, set<string> &s2) {
    set<string> intersectSet;
    set_intersection(s1.begin(), s1.end(),s2.begin(), s2.end(), inserter(intersectSet, intersectSet.begin()));
    cout << "intersectSet" << "\n";
    for (auto& i : intersectSet) {
        cout << i << " ";
    }
    cout << "\n";
    return intersectSet;
}
set<string> Jaccard::getUnionSet(set<string> &s1, set<string> &s2) {
    set<string> unionSet;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(unionSet, end(unionSet)));
    cout << "unionSet" << "\n";
    for (auto& i : unionSet) {
        cout << i << " ";
    }
    cout << "\n";
    return unionSet;
}
/**
 * Jaccard index
 * J (s1, s2) = intersection of s1 and s2 / union of s1 and s2
 */
double Jaccard::getJaccardIndex(set<string> s1, set<string> s2) {
    set<string> xset = getIntersectionSet(s1, s2);
    set<string> uset = getUnionSet(s1, s2);
    double lenxset = xset.size(), lenuset = uset.size();
    return lenxset / lenuset;
}