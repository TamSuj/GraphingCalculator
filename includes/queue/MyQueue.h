#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>
#include "assert.h"

using namespace std;

#include "../linked_list_functions/linked_list_functions.h"
#include "../list_sorted/list_sorted.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator()                  //default ctor
        {
            _ptr = nullptr;
        }
        Iterator(node<T>* p)        //Point Iterator to where
        {
            _ptr = p;
        }
        //...                        //  p is pointing to
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
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <typename T> 
Queue<T>::Queue() : _front(nullptr), _rear(nullptr), _size(0) { }

template <typename T> 
Queue<T>::Queue(const Queue<T>& copyMe)
{
    _front = nullptr;
    _clear_list(_front);
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
    
}

template <typename T> 
Queue<T>::~Queue()
{
    _clear_list(_front);
}

template <typename T> 
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;

    return *this;
}

template <typename T> 
bool Queue<T>::empty()
{
    return _size == 0;
}

template <typename T> 
T Queue<T>::front()
{
    return _front->_item;
}

template <typename T> 
T Queue<T>::back()
{
    if(empty())
        throw invalid_argument("Queue is empty");

    return _rear->_item;
}

template <typename T> 
void Queue<T>::push(T item)
{
    if(_size == 0)
    {
        _front = _insert_head(_front, item);
        _rear = _front;
    }
    else{
        _rear = _insert_after(_front, _rear, item);
    }
    
    _size++;
}
template <typename T> 
T Queue<T>::pop()
{
    if(empty())
        throw invalid_argument("Queue is empty");

    T temp = _front->_item;
    _delete_head(_front);
    _size--;

    return temp;
}

template <typename T>   
typename Queue<T>::Iterator Queue<T>::begin() const            //Iterator to the head node
{
    return typename Queue<T>::Iterator(_front);
}

template <typename T> 
typename Queue<T>::Iterator Queue<T>::end() const              //Iterator to NULL
{
    return typename Queue<T>::Iterator(nullptr);
}

template <typename T>            
void Queue<T>::print_pointers(){
    cout << "front: " << front() << endl;
    cout << "rear: " << back() << endl;
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){

    for(typename Queue<TT>::Iterator it = printMe.begin(); it != printMe.end(); it++){
            outs << *it << " -> ";
    }    
    outs << "|||";
    
    return outs;
}

#endif