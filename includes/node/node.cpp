#ifndef NODE_CPP
#define NODE_CPP

#include "node.h"

template <typename ITEM_TYPE>
node<ITEM_TYPE>::node(const ITEM_TYPE& item, node* next)
: _item(item), _next(next)
{
}

template <typename T>
ostream& operator <<(ostream& outs,const node<T> &printMe)
{
    outs << printMe._item << " ";
    return outs;
}

#endif

