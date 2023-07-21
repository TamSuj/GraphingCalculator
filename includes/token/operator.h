#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <iomanip>
#include "token.h"
#include <cmath>

using namespace std;

class Operator : public Token
{
public:
    Operator(const string& op = "") : Token(op, 2){
        _prec = get_prec(op);
    }
    int get_prec(const string& op) {
        switch(token()[0]) {
            case '+':
                return 1;
            case '-':
                return 1;
            case '*':
                return 2;
            // case ' ':
            //     return 2;
            case '/':
                return 2;
            case '^':
                return 3;
            case 'X':
                return 4;
        default:
            break;
            
        }
        return 4; //for all the function
    }

    double eval(double LHS, double RHS) {
        double result = 0;

        switch(getSign()[0]){
            case '+':
                result = LHS + RHS;
                break;
            case '-':
                result = LHS - RHS;
                break;
            case '*':
                result = LHS * RHS;
                break;
            case ' ':
                result = LHS * RHS;
                break;
            case '/':
                if (RHS == 0)
                    throw invalid_argument("division by zero");
                result = LHS / RHS;
                break;
            case '^':
                result = pow(LHS, RHS);
                break;
        }
        return result;
    }
    void Print(ostream& outs){
        outs << token();
    }

    void type(){ }
    double 
    getValue() { return _prec; }
    string getSign() { return token(); }
private:
    double _prec;

};

#endif