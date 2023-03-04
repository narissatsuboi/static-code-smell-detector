// Your First C++ Program
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// skip comments
// int addition(int a, int b)
/* int addition(int a, int b)
 * int addition(int a, int b)
 */

//truth_table_entry(false, false);

int addition(int a, int b) {
    if (a < b) {
        cout << "a";
    } else if (a > b) {
        continue;
    }
    else {
        cout << "b";
    };

    return a + b;
}

unordered_map<string, vector<string>> randomFunc() {
    return unordered_map<string, vector<string>>();
}
int main() {
    std::cout << "Hello World!";
    return 0;
}
