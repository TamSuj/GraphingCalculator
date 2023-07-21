#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <assert.h>
using namespace std;

#include "../node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head)
{
    for(node<T>* walker = head; walker != nullptr; walker = walker->_next)
    {
        cout << "[" << walker->_item << "]-> ";
    }
    cout << "|||";
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    for(node<T>* w = head; w != nullptr; w = w->_next)
    {
        if(w->_item == key)
            return w;
    }
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this)
{
    node<T>* newNode = new node<T>(insert_this, head);
    head = newNode;

    return newNode;
}

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this)
{
    // assert(after_this != nullptr);
    if(head == nullptr) //insert head
        return _insert_head(head, insert_this);
    else
    {
        node<T>* newNode = new node<T>(insert_this);
        node<T>* temp = after_this->_next;
        after_this->_next = newNode;
        newNode->_next = temp;

        return newNode;
    }
    return nullptr;
}

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this)
{
    //Insert a new node before the node pointed to by before_this
    //return a pointer to the new node
    //if before_this is the head, insert a new head
    //if before_this is NULL, insert at the end of the list

    if(head == nullptr)
        return _insert_head(head, insert_this);
    else if(before_this == nullptr)
        return _insert_after(head, _last_node(head), insert_this);
    else if(before_this == head)
        return _insert_head(head, insert_this);
    else
    {
        node<T>* newNode = new node<T>(insert_this);
        node<T>* prev = _previous_node(head, before_this);
        prev->_next = newNode;
        newNode->_next = before_this;

        return newNode;
    } 
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this)
{
    assert(head != nullptr && prev_to_this != nullptr);

    if(prev_to_this == head)
        return nullptr;

    node<T>* walker = head;
    while(walker->_next != prev_to_this)
    {
        walker = walker->_next;
    }
    
    //move forward as long as walker->_next is not the same as prev_to_this
    return walker;
}                   

//delete, return item
template <typename T>
T _delete_node(node<T>*&head, node<T>* delete_this)
{
    T pop;

    assert(head != nullptr);
    assert(delete_this != nullptr);

    if (delete_this == head)
    { //remove headptr
        pop = head->_item;
        head = head->_next;
    }
    else{
        node<T>* prev = _previous_node(head, delete_this);
           pop = delete_this->_item;
           prev->_next =  delete_this->_next;     
    }
    delete  delete_this;
    //return value inside the node we remove
    return pop;
}
//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head)
{
    node<T>* newHead = nullptr;
    for(node<T>* w = head; w != nullptr; w = w->_next)
    {
        _insert_after(newHead, _last_node(newHead), w->_item);
    }

    return newHead;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src)
{
    if(src == nullptr)
        return nullptr;
    dest = new node<T>(src->_item);
    for(node<T>* w = src->_next; w != nullptr; w = w->_next)
    {
        _insert_after(dest, _last_node(dest), w->_item);
    }

    return _last_node(dest);
}


//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head)
{
    while(head != nullptr){
        node<T>* hold = head;
        head = head->_next;
        delete hold;
    }
    head = nullptr;
}

template <typename T>
void _delete_head(node<T>*& head)
{
    node<T>* hold = head;
    head = head->_next;
    delete hold;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos)
{
    assert(pos >= 0);
    // assert(head != nullptr);
    int i = 0;
    for(node<T>* w = head; w != nullptr; w = w->_next)
    {
        if(i == pos)
            return w->_item;
        i++;
    }
    return head->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// template <typename T>
// node<T>* _insert_sorted(node<T>* &head, T item, bool ascending=true)
// {
//     node<T> *marker = _where_this_goes(head, item, ascending);

//     if(_search_list(head, item) != nullptr)
//         return _insert_sorted_and_add(head, item, ascending);

//     if(marker == nullptr)
//         return _insert_head(head, item);
//     else
//         return _insert_after(head, marker, item);
    
// }
template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending=true)
{
    node<T> *marker = head;

    if(ascending)
    {
        for(node<T> *w = head; w != nullptr; w = w->_next)
        {
            if(item < w->_item)
                marker = w;
        }
        return _insert_after(head, marker, item);
    }else{
        for(node<T> *w = head; w != nullptr; w = w->_next)
        {
            if(item > w->_item)
                marker = w;
        }
        return _insert_before(head, marker, item);
    }

    
}

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head,
                                        T item,
                                        bool ascending=true)
{

    if(_search_list(head, item) != nullptr)
    {
        for(node<T> *w = head; w != nullptr; w = w->_next)
        {
            if(item == w->_item)
            {
                w->_item += item;
                return w;
            }
        }
    }
    
    return _insert_sorted(head, item, ascending); 
}
//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending = true)
{

    if(ascending)
    {    
        for(node<T> *w = head; w != nullptr; w = w->_next)
        {
            if(item > w->_item)
                return w->_next;
        }
    }
    else
    {
        for(node<T> *w = head; w != nullptr; w = w->_next)
        {
            if(item < w->_item)
                return w->_next;
        }
    }

    return nullptr;
}                                
//Last Node in the list
template <typename T>
node<T>* _last_node(node<T>* head)            //never use this function.
{
    if(head == nullptr)
        return nullptr;

    node<T>* last_node = head;
    while (last_node->_next != nullptr) 
    {
        last_node = last_node->_next;
    }

    return last_node;
}

#endif