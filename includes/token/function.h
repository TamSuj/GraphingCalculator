#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include "token.h"
#include "operator.h"

using namespace std;

//Ex: sin(x), cos(x)
// class Function : public Operator
class Function : public Operator
{
public:
    Function();
    Function(const string& fx = "X") : Operator(fx) { }
    void Print(ostream& outs){
        outs << token() << endl;
    }
    void type(){ }
};



#endif

//-1 is variable
/*
Public:
Token *eval();

int num_of_args(){
    sin: 1
    cos: 1
    log: 2
    "x": -1
}

Token* p = new Function('sin')

*/