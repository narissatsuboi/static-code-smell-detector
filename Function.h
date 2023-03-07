//
// Created by nars on 3/6/2023.
//

#ifndef SNIFFY_FUNCTION_H
#define SNIFFY_FUNCTION_H
#include <string>
using namespace std;

class Function
{
private:

public:
    string handle;
    int start{};
    int end{};
    int loc{};
    int paramCount = 0;

    Function();
    Function(int &startLine, string &handle, string &fullSignature);
    bool isLongMethod() const;
    bool isLongParams() const;
    bool isDupCode();
};


#endif //SNIFFY_FUNCTION_H
