#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include "../stack/MyStack.h"

using namespace std;

class Token
{
public:
    Token() {}
    Token(const string& s = "?", int type = 0) : _token(s), _type(type){ }
    virtual void Print(ostream& outs) const { }
    virtual void type() = 0;
    friend ostream &operator<<(ostream &os, const Token&t){
        t.Print(os);
        return os;
    }

    string token() { return _token; }
    int getType() {return _type; }

private:
    int _type; //1 = Integer, 2 = operator
    string _token;
};

#endif