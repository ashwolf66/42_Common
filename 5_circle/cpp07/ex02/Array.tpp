#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _arr(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _arr(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(const Array& other) : _arr(NULL), _size(0) {
    *this = other;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] _arr;
        _size = other._size;
        _arr = new T[_size];
        for (unsigned int i = 0; i < _size; ++i)
            _arr[i] = other._arr[i];
    }
    return *this;
}

template <typename T>
Array<T>::~Array() {
    delete[] _arr;
}

template <typename T>
T& Array<T>::operator[](unsigned int i) {
    if (i >= _size)
        throw std::out_of_range("Index out of range");
    return _arr[i];
}

template <typename T>
const T& Array<T>::operator[](unsigned int i) const {
    if (i >= _size)
        throw std::out_of_range("Index out of range");
    return _arr[i];
}

template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}

#endif
