#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <typename ITEM_TYPE>
struct node
{
public:
    node(const ITEM_TYPE& item = ITEM_TYPE(), node* next = nullptr);

    template <typename T>
    friend ostream& operator <<(ostream& outs,
                                const node<T> &printMe);
    ITEM_TYPE _item;
    node* _next;
};


#include "node.cpp"
#endif