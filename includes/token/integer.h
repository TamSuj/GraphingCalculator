#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <iomanip>

#include "token.h"

using namespace std;

class Integer : public Token
{
public:
    Integer(double i = 0) : Token(to_string(i), 1), _value(i) {}
    // virtual void Print(ostream& outs);
    Integer(const string& n = "0.0") : Token(n, 1), _value(stod(n)) {}
    void int_only() { cout << "Integer only" << endl;}
    //use to test casting (when calling child function from parent)

    void Print(ostream& outs)
    {
        outs << _value << endl;
    }
    
    void type() { }
    double getValue() { return _value; }

private:
    double _value;


};

#endif