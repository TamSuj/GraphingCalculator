#ifndef LIST_SORTED_CPP
#define LIST_SORTED_CPP

#include "list_sorted.h"

template<typename T>
List<T>::List(bool order, bool unique) : _size(0), _head_ptr(nullptr) {

}

template<typename T>
List<T>::~List() {
    _clear_list(_head_ptr);
    _size = 0;
}

template<typename T>
List<T>::List(const List<T> &copyThis) {
    _head_ptr = _copy_list(copyThis._head_ptr);
    _size = copyThis._size;
}

template<typename T>
List<T> &List<T>::operator=(const List &RHS) {
    if(&RHS == this)
        return *this;

    _head_ptr = _copy_list(RHS._head_ptr);
    _size = RHS._size;

    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(const T &i) {
    _size++;
    return Iterator(_insert_sorted(_head_ptr, i));
}

template<typename T>
typename List<T>::Iterator List<T>::insert_and_add(const T &i) {
    _size++;
    return Iterator(_insert_sorted_and_add(_head_ptr, i));
}

template<typename T>
T List<T>::Delete(List<T>::Iterator iMarker) {
    assert(_size > 0);
    _size--;
    return _delete_node(_head_ptr, iMarker._ptr);
}

template<typename T>
void List<T>::Print() const {
    _print_list(_head_ptr);
}

template<typename T>
typename List<T>::Iterator List<T>::search(const T &key) const {
    return Iterator(_search_list(_head_ptr, key));
}

template<typename T>
typename List<T>::Iterator List<T>::prev(List::Iterator iMarker) {
    return Iterator(_previous_node(_head_ptr, iMarker._ptr));
}

template<typename T>
const T &List<T>::operator[](int index) const {
    return _at(_head_ptr, index);
}   

template<typename T>
T &List<T>::operator[](int index) {
    return _at(_head_ptr, index);
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return List::Iterator(_head_ptr);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return List::Iterator(nullptr);
}

template<typename T>
typename List<T>::Iterator List<T>::last_node() const {
    return List::Iterator(_last_node(_head_ptr));
    

}

#endif
