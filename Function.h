/**
 * @file Function.h
 * @author Narissa Tsuboi
 */

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
    bool longmethod{};
    int paramCount{};
    bool longparams{};
    bool dupcode{};

    Function();

    Function(int &startLine, string &name, string &fullSignature);

    bool dupCode();



    friend ostream& operator<<(ostream& os, const Function& func);
};
#endif //SNIFFY_FUNCTION_H
