#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <iomanip>
#include "assert.h"
#include <cmath>

using namespace std;

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/integer.h"
#include "../token/operator.h"

class RPN
{
public:
    RPN() {}
    RPN(Queue<Token*> &inputQueue) : tokenQueue(inputQueue) {}
    void set_input(Queue<Token *> iniQueue);
    double operator()(double value = 0);

private:
    Queue<Token*> tokenQueue;

};

double RPN::operator()(double value){
    
    Stack<Token*> myStack;
    double result = 0;

    // Queue<Token*> postFix = tokenQueue; //use iterator instead

    // while(!postFix.empty())
    // {
    //     assert(postFix.front()->getType() != 3); //assert there's no parenthesis

    //     if(postFix.front()->getType() == 1) //number
    //     {
    //         myStack.push(postFix.pop());
    //     }
    //     else if(postFix.front()->getType() == 2)
    //     {
    //         if(static_cast<Operator*>(postFix.front())->getValue() == 4) //function's precedence = 4
    //         {
    //             if(postFix.front()->token() == "X"){
    //                 myStack.push(new Integer(value));
    //                 postFix.pop();
    //             }
    //             else 
    //             {
    //                 double RHS = static_cast<Integer&>(*myStack.pop()).getValue();
                
    //                 if(postFix.front()->token() == "!")
    //                 {
    //                     result = 1;
    //                     for(int i = 1; i <= RHS; i++)
    //                         result *= i;
    //                 }
    //                 else if(postFix.front()->token() == "sin")
    //                 {
    //                     result = sin(RHS);
    //                 }
    //                 else if(postFix.front()->token() == "cos")
    //                 {
    //                     result = cos(RHS);
    //                 }
    //                 else if(postFix.front()->token() == "tan")
    //                 {
    //                     result = tan(RHS);
    //                 }
    //                 else if(postFix.front()->token() == "log")
    //                 {
    //                     if (RHS <= 0)
    //                         throw invalid_argument("logarithm of non-positive number");
                    
    //                     result = log(RHS);
    //                 }
    //                 else if(postFix.front()->token() == "sqrt")
    //                 {
    //                     if (RHS < 0) 
    //                         throw invalid_argument("square root of negative number");
    //                     result = sqrt(RHS);
    //                 }
    //                 else if(postFix.front()->token() == "abs")
    //                 {
    //                     result = abs(RHS);
    //                 }
                    
    //                 myStack.push(new Integer(result));
    //                 postFix.pop();
    //             }
    //         }
    //         else //if it's operator (not function), pop stack twice, perform math operation, then put it back to stack
    //         {
    //             Operator& sign = static_cast<Operator&>(*postFix.pop());

    //             if(myStack.size() >= 2){
            
    //                 double RHS = static_cast<Integer&>(*myStack.pop()).getValue();
    //                 double LHS = static_cast<Integer&>(*myStack.pop()).getValue();                    
    //                 // switch(sign.getSign()[0])
    //                 // {
    //                 //     case '+':
    //                 //         result = LHS + RHS;
    //                 //         break;
    //                 //     case '-':
    //                 //         result = LHS - RHS;
    //                 //         break;
    //                 //     case '*':
    //                 //         result = LHS * RHS;
    //                 //         break;
    //                 //     case ' ':
    //                 //         result = LHS * RHS;
    //                 //         break;
    //                 //     case '/':
    //                 //         if (RHS == 0)
    //                 //             throw invalid_argument("division by zero");
    //                 //         result = LHS / RHS;
    //                 //         break;
    //                 //     case '^':
    //                 //         result = pow(LHS, RHS);
    //                 //         break;
    //                 // }
    //                 //myStack.push(new Integer(result));

    //                 result = sign.eval(LHS, RHS);
    //                 myStack.push(new Integer(result));
    //             }
    //             else
    //                 throw invalid_argument("not enough operands");
    //         }
            
    //     }
        
    // }

    // if(myStack.empty())
    //     return 0;

    // return static_cast<Integer&>(*myStack.pop()).getValue();


    for (Queue<Token *>::Iterator it = tokenQueue.begin(); it != tokenQueue.end(); it++)
    {
        assert((*it)->getType() != 3); //assert there's no parenthesis


        if((*it)->getType() == 1) //number
        {
            myStack.push(*it);
        }
        else if((*it)->getType() == 5) //variable
        {
            myStack.push(new Integer(value));
        }
        else if((*it)->getType() == 2) //operator
        {
            if(static_cast<Operator*>((*it))->getValue() == 4) //function's precedence = 4
            {
                if((*it)->token() == "pi" || (*it)->token() == "PI")
                {
                    result = 22/7;
                    //3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

                }else if((*it)->token() == "e"){
                    result = 2.71828;
                }
                else{
                    
                    double RHS = static_cast<Integer&>(*myStack.pop()).getValue();
                
                    if((*it)->token() == "!")
                    {
                        result = 1;
                        for(int i = 1; i <= RHS; i++)
                            result *= i;
                    }
                    else if((*it)->token() == "sin")
                    {
                        result = sin(RHS);
                    }
                    else if((*it)->token() == "cos")
                    {
                        result = cos(RHS);
                    }
                    else if((*it)->token() == "tan")
                    {
                        result = tan(RHS);
                    }
                    else if((*it)->token() == "log")
                    {
                        if (RHS <= 0)
                            throw invalid_argument("logarithm of non-positive number");
                    
                        result = log(RHS);
                    }
                    else if((*it)->token() == "sqrt")
                    {
                        if (RHS < 0) 
                            throw invalid_argument("square root of negative number");
                        result = sqrt(RHS);
                    }
                    else if((*it)->token() == "abs")
                    {
                        result = abs(RHS);
                    }
                }
                
                myStack.push(new Integer(result)); 
            }
            else //if it's operator (not function), pop stack twice, perform math operation, then put it back to stack
            {
                Operator& sign = static_cast<Operator&>(*(*it));

                if(myStack.size() >= 2){
            
                    double RHS = static_cast<Integer&>(*myStack.pop()).getValue();
                    double LHS = static_cast<Integer&>(*myStack.pop()).getValue();                    

                    result = sign.eval(LHS, RHS);
                    myStack.push(new Integer(result));
                }
                else
                    throw invalid_argument("not enough operands");
            }  
        }
    }
    if(myStack.empty())
        return 0;

    return static_cast<Integer&>(*myStack.pop()).getValue();
}

void RPN::set_input(Queue<Token *> iniQueue)
{
    tokenQueue = iniQueue;
}
#endif