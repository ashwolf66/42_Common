/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:32:48 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:32:50 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _arr(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _arr(new T[n]()), _size(n)
{
}

template <typename T>
Array<T>::Array(const Array &other) : _arr(NULL), _size(0)
{
    *this = other;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
    if (this != &other)
    {
        delete[] _arr;
        this->_size = other._size;
        this->_arr = new T[_size];
        for (unsigned int i = 0; i < this->_size; ++i)
            this->_arr[i] = other._arr[i];
    }
    return (*this);
}

template <typename T>
Array<T>::~Array()
{
    if (this->_arr != NULL)
        delete[] this->_arr;
}

template <typename T>
T &Array<T>::operator[](unsigned int i)
{
    if (i >= this->_size || this->_arr == NULL)
        throw(Array::BadIndex());
    return (this->_arr[i]);
}

template <typename T>
const T &Array<T>::operator[](unsigned int i) const
{
    if (i >= this->_size || this->_arr == NULL)
        throw(Array::BadIndex());
    return (this->_arr[i]);
}

template <typename T>
unsigned int Array<T>::getSize() const
{
    return (this->_size);
}

template <typename T>
const char *Array<T>::BadIndex::what() const throw()
{
    return ("Bad Index!!!!");
}

#endif
