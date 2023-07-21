#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>
#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"
#include "../list_sorted/list_sorted.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                //default ctor
        Iterator(node<T>* p){_ptr =p;}          //Point Iterator to where
                                                //  p is pointing to
        T &operator*()
        {
            assert(_ptr);
            return _ptr->_item;
        }
                                     //dereference operator

        T *operator->()
        {
            return &(_ptr->_item);
        }                            //member access operator
        bool is_null(){
            return _ptr == nullptr;
        }                             //true if _ptr is NULL
        friend bool operator!=(const Iterator &left, const Iterator &right)
        {
            return left._ptr != right._ptr;
        } //true if left != right

        friend bool operator==(const Iterator &left, const Iterator &right)
        {
            return left._ptr == right._ptr;
        } //true if left == right

        Iterator &operator++()
        {
            assert(_ptr);

            _ptr = _ptr->_next;
            return *this;
        }                         //member operator:
                                                        //  ++it; or
                                                        //  ++it = new_value

        friend Iterator operator++(Iterator &it, int unused)
        {
            assert(it._ptr);

            Iterator temp = it;
            it._ptr = (it._ptr)->_next;
            return temp;
        }          //friend operator: it++
    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe);

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top = nullptr;
    int _size;
};
template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe)
    {
        for(typename Stack<TT>::Iterator it = printMe.begin(); it != printMe.end(); it++)
            outs << *it << " -> ";
        
        outs << "|||";
        return outs;
    }

template <typename T>
Stack<T>::Stack() : _size(0), _top(nullptr) { }

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe)
: _size(copyMe._size)
{
    _copy_list(_top, copyMe._top);
}

template <typename T>
Stack<T>::~Stack(){
    _clear_list(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS)
{
    if(this != &RHS)
    {
        _clear_list(_top);
        _copy_list(_top, RHS._top);
    }
    _size = RHS._size;
    
    return *this;
}

template <typename T>
T Stack<T>::top()
{
    if (empty())
        throw invalid_argument("Stack is empty");
    
    return _top->_item;
}

template <typename T>
bool Stack<T>::empty()
{
    return _size == 0;
}

template <typename T>
void Stack<T>::push(T item)
{
    _insert_head(_top, item);
    _size++;
}

template <typename T>
T Stack<T>::pop()
{
    if (empty())
        throw invalid_argument("Stack is empty");

    T temp = top();
    _delete_head(_top);
    _size--;

    return temp;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const              //Iterator to the head node
{
    return Iterator(_top);
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const                //Iterator to NULL
{
    return Iterator(nullptr);
}

#endif