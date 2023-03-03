// Your First C++ Program

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<string>> functionOne(string& s) {
    return unordered_map<string, vector<string>>();
}

unordered_map<int, unordered_map<string, vector<string>>> functionTwo(string& s) {
    return unordered_map<int, unordered_map<string, vector<string>>> ();
}

int main() {
    std::cout << "Hello World!";
    return 0;
}
