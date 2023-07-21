#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include <iostream>
#include <iomanip>
#include "token.h"

class LeftParen : public Token
{
public:
    LeftParen(const string& x = "(") : Token(x, 3) {}
    void Print(ostream& outs){
        outs << token() << endl;
    }
    void type() {}

private:


};


#endif