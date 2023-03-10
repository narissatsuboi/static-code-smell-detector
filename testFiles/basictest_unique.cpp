// Your First C++ Program

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void LPLfunction(string& a, int b, int c, int d);


int easyMethod() {
    if (true) {
        cout << "yeehaw";
    } else {
        cout << "bogus";
    }
}


class PlainBox
{
private :
// Data ﬁeld
    ItemType item;
public :
// Default constructor
    PlainBox();

// Parameterized constructor
    PlainBox(const ItemType &theItem);

// Method to change the value of the data ﬁeld
    void setItem(const ItemType &theItem);

// Method to get the value of the data ﬁeld
    ItemType getItem() const;
}; // end PlainBox


unordered_map<string, vector<string>> functionOne(string& s) {
    return unordered_map<string, vector<string>>();
}

unordered_map<int, unordered_map<string, vector<string>>> functionTwo(string& s) {
    return unordered_map<int, unordered_map<string, vector<string>>> ();
}


// detect
unordered_map<int, unordered_map<string, vector<string>>> functionTwo(string&);

Cat::Cat() = default;
Cat();


// no detect
Cat myCat = new Cat();


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
