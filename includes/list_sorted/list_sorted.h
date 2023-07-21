#ifndef LIST_SORTED_H
#define LIST_SORTED_H

#include <iostream>
using namespace std;
#include "assert.h"

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class List
{
public:
    class Iterator{
    public:
        friend class List;                          //give access to list to
                                                    //          access _ptr
        Iterator(){_ptr = NULL;}                    //default ctor
        Iterator(node<T>* p) : _ptr(p){ }
                                                    //Point Iterator to where p
                                                    //  is pointing to
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
        friend bool operator!=(const Iterator &left,
                               const Iterator &right)
        {

            return left._ptr != right._ptr;
        } //true if left != right

        friend bool operator==(const Iterator &left,
                               const Iterator &right)
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

        friend Iterator operator++(Iterator &it,
                                   int unused)
        {
            assert(it._ptr);

            Iterator temp = it;
            it._ptr = (it._ptr)->_next;
            return temp;
        }          //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    List(bool order=true, bool unique=false);           //CTOR: default args
                                                        //BIG 3:
    ~List();
    List(const List<T> &copyThis);
    List& operator =(const List& RHS);

    Iterator insert(const T& i);                        //Insert i
    Iterator insert_and_add(const T& i);                //Insert i

    T Delete(List<T>::Iterator iMarker);                //delete node at marker
    void Print() const;
    Iterator search(const T &key) const;                //return Iterator to
                                                        //          node [key]
    Iterator prev(Iterator iMarker);                    //previous node: marker

    const T& operator[](int index) const;               //const version of the
                                                        //       operator [ ]
    T& operator[](int index);                           //return item at index
    Iterator begin() const;                             //Iterator to head node
    Iterator end() const;                               //Iterator to NULL
    Iterator last_node() const;                          //Iterator to last node
    bool empty() const { return _head_ptr == nullptr; }
    template <class U>                                  //Note template arg U
    friend ostream& operator <<(ostream& outs, const List<U>& l){
        _print_list(l._head_ptr);
        return outs;
    }
    int size() const { return _size; }

private:
    node<T>* _head_ptr = nullptr;
    bool _order;
    bool _unique;
    int _size;
};



#include "list_sorted.cpp"

#endif