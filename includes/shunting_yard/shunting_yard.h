#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

#include "../token/integer.h"
#include "../token/operator.h"

class ShuntingYard
{
public:
    ShuntingYard(){}
    ShuntingYard(Queue<Token*> myQueue) : tokenQueue(myQueue) { }
    Queue<Token*> postfix();
    Queue<Token*> postfix(Queue<Token*> infixQueue);
    Queue<Token*> infix(Queue<Token*> fixMe);

private:
    Queue<Token*> tokenQueue;

};

Queue<Token*> ShuntingYard::postfix() //prefix -> postfix
{
    /*
    1. Initialize two empty data structures: a queue for the output and a stack for operators.
    2. Read each token (usually numbers and operators) from left to right:
        - If the token is a number or variable, add it to the output queue.
        - If the token is an operator, compare its precedence with that of the operator on top of the stack:
            > If the operator on top of the stack has higher or equal precedence, pop it from the stack and add it to the output queue.
            > If the operator on top of the stack has equal or lower precedence, push the new operator onto the stack.
        - If the token is a left parenthesis, push it onto the stack.
        - If the token is a right parenthesis, pop operators from the stack and add them to the output queue until a left parenthesis is found, which is then discarded.
    3. Continue until all tokens have been read.
    4. Pop any remaining operators from the stack and add them to the output queue.
    5. The resulting postfix expression can be evaluated by reading each token from left to right and either adding it to a stack (if it is a number) or performing the appropriate operation (if it is an operator).*/
    
    return postfix(tokenQueue);
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> infixQueue) //prefix -> postfix
{
    Queue<Token*> postFix;
    Stack<Token*> operStack;

    while(!infixQueue.empty())
    {
        //if integer or variable
        if(infixQueue.front()->getType() == 1 || infixQueue.front()->getType() == 5)
        {
            postFix.push(infixQueue.pop());
        }
        else if(infixQueue.front()->getType() == 2) //if it's operator
        {   
            if(operStack.empty())
            {
                operStack.push(infixQueue.pop());
                continue;
            }
            else{
                if(operStack.top()->getType() == 2)
                {  
                    //Check precedence
                    while(!operStack.empty() && static_cast<Operator*>(operStack.top())->getValue() >= static_cast<Operator*>(infixQueue.front())->getValue())
                    {
                        postFix.push(operStack.pop());
                    }
                }
                operStack.push(infixQueue.pop());
            }
        }
        else if(infixQueue.front()->getType() == 3) // parentheses
        {
            if(infixQueue.front()->token() == "(") //left parentheses
            { 
                operStack.push(infixQueue.pop());
            }
            else //right parentheses
            { 
                infixQueue.pop(); //pop out right parentheses
                //pop operator from operStack until spot )
                while(!operStack.empty() && operStack.top()->token() != "("){
                    postFix.push(operStack.pop());
                }   
                
                assert(operStack.pop()->token() == "("); //pop out left parentheses          
            }
        }
        else if(infixQueue.front()->getType() == 4){ //function
            operStack.push(infixQueue.pop()); 
            //issue: give function highest precedency and it should work
        }
    }

    while(!operStack.empty())
    {
        postFix.push(operStack.pop());
    }

    return postFix;

    /*
    pop operator as long as stack is not empty and the top pf stack >= operator in queue*/
}

Queue<Token*> ShuntingYard::infix(Queue<Token *> fixMe)
{
    tokenQueue = fixMe;
    return tokenQueue;
}

#endif



//infix 3 + 8 -> shunting yard -> 3 8 + -> rpn -> 11