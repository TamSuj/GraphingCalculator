#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <iomanip>
#include "token.h"
#include <cmath>

using namespace std;

class Variable : public Token
{
public:
    Variable() : Token("X", 5) {}
    // virtual void Print(ostream& outs);
    Variable(const string& var = "X") : Token(var, 5), _variable(var) {}
    void Print(ostream& outs)
    {
        outs << token() << endl;
    }
    
    void type() { }
    string getValue() { return _variable; }

private:
    string _variable = "X";


};

#endif