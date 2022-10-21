#pragma once

#include <numeric>

#include "rowcolumn.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
ColumnIterator<Number, Rows, Cols>::ColumnIterator(typename std::array<Number, Rows * Cols>::iterator iterator):
    _iterator{iterator} {}

template<class Number, std::size_t Rows, std::size_t Cols>
ColumnIterator<Number, Rows, Cols> ColumnIterator<Number, Rows, Cols>::operator++() {
    _iterator += Cols;
    return *this;
}

template<class Number, std::size_t Rows, std::size_t Cols>
bool ColumnIterator<Number, Rows, Cols>::operator!=(ColumnIterator other) {
    return _iterator != other._iterator;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Number& ColumnIterator<Number, Rows, Cols>::operator*() const {
    return *_iterator;
}



template<class Number, std::size_t Rows, std::size_t Cols>
Column<Number, Rows, Cols>::Column(typename std::array<Number, Rows * Cols>& initial, std::size_t idx):
    _begin{initial.begin() + idx},
    _end{initial.begin() + idx + Rows * Cols} 
{
    if (idx >= Cols) {
        throw std::invalid_argument("column idx out of boundaries");
    }
}

template<class Number, std::size_t Rows, std::size_t Cols>
ColumnIterator<Number, Rows, Cols> Column<Number, Rows, Cols>::begin() {
    return ColumnIterator<Number, Rows, Cols>(_begin);
}

template<class Number, std::size_t Rows, std::size_t Cols>
ColumnIterator<Number, Rows, Cols> Column<Number, Rows, Cols>::end() {
    return ColumnIterator<Number, Rows, Cols>(_end);
}

template<class Number, std::size_t Rows, std::size_t Cols>
std::array<Number, Rows> Column<Number, Rows, Cols>::copy() {
    std::array<Number, Rows> result;
    std::transform(begin(), end(), result.begin(), [](Number elem) {return elem;});
    return result;
}


template<class Number, std::size_t Rows, std::size_t Cols>
RowIterator<Number, Rows, Cols>::RowIterator(typename std::array<Number, Rows * Cols>::iterator iterator):
    _iterator{iterator} {}

template<class Number, std::size_t Rows, std::size_t Cols>
RowIterator<Number, Rows, Cols> RowIterator<Number, Rows, Cols>::operator++() {
    _iterator += 1;
    return *this;
}

template<class Number, std::size_t Rows, std::size_t Cols>
bool RowIterator<Number, Rows, Cols>::operator!=(RowIterator other) {
    return _iterator != other._iterator;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Number& RowIterator<Number, Rows, Cols>::operator*() const {
    return *_iterator;
}


template<class Number, std::size_t Rows, std::size_t Cols>
Row<Number, Rows, Cols>::Row(typename std::array<Number, Rows * Cols>& initial, std::size_t idx):
    _begin{initial.begin() + Cols * idx},
    _end{initial.begin() + Cols * idx + Cols} 
{
    if (idx >= Rows) {
        throw std::invalid_argument("row idx out of boundaries");
    }
}

template<class Number, std::size_t Rows, std::size_t Cols>
RowIterator<Number, Rows, Cols> Row<Number, Rows, Cols>::begin() {
    return RowIterator<Number, Rows, Cols>(_begin);
}

template<class Number, std::size_t Rows, std::size_t Cols>
RowIterator<Number, Rows, Cols> Row<Number, Rows, Cols>::end() {
    return RowIterator<Number, Rows, Cols>(_end);
}

template<class Number, std::size_t Rows, std::size_t Cols>
std::array<Number, Cols> Row<Number, Rows, Cols>::copy() {
    std::array<Number, Cols> result;
    std::transform(begin(), end(), result.begin(), [](Number elem) {return elem;});
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
template<std::size_t SecondCols>
Number Row<Number, Rows, Cols>::operator*(Column<Number, Cols, SecondCols> other) {
    return std::inner_product(begin(), end(), other.begin(), 0);
}