#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include <iostream>
#include <iomanip>
#include "token.h"


class RightParen : public Token
{
public:
    // RightParen() : Token(")", 3) {}
    RightParen(const string& x = ")") : Token(x, 3) {}
    void Print(ostream& outs){
        outs << token() << endl;
    }
    void type() {}

private:


};


#endif