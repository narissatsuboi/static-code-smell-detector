// Your First C++ Program

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


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


int main() {
    std::cout << "Hello World!";
    return 0;
}
