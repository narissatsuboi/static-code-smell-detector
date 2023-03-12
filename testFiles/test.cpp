/**
 * @file test1.cpp
 * @author Narissa Tsuboi
 */
#include <iostream>

using namespace std;

// loc = 1 blanks - 0
int main1() { for (int i = 0; i < 10; i++) { cout << "Hi" << endl; }}

// loc = 2 blanks = 1
int main2() {

}

// loc = 3 blanks = 1
int main3()
{

}

// loc = 3 blanks = 0
int main4() {
    for (int i = 0; i < 10; i++) { cout << "Hi" << endl; }
}

//int fun1(int a, int b, int c, int d) {
//    return a + b;
//}
//
//int fun23456(int a, int b, int c, int d) {
//    return a + b;
//}
//
//int fun3(int a, int b, int y, int z) {
//    return a + b;
//}
//
//int main() {
//    int n, t1 = 0, t2 = 1, nextTerm = 0;
//
//    cout << "Enter the number of terms: ";
//    cin >> n;
//
//    cout << "Fibonacci Series: ";
//
//    for (int i = 1; i <= n; ++i) {
//        if (i == 1) {
//            cout << t1 << ", ";
//            continue;
//        }
//        if (i == 2) {
//            cout << t2 << ", ";
//            continue;
//        }
//        nextTerm = t1 + t2;
//        t1 = t2;
//        t2 = nextTerm;
//
//        cout << nextTerm << ", ";
//    }
//    return 0;
//}
