#pragma once

#include "rowcolumnlist.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
ColumnListIterator<Number, Rows, Cols>::ColumnListIterator(typename std::array<Number, Rows * Cols>& initial, std::size_t idx):
    _idx{idx},
    _matrix{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>    
ColumnListIterator<Number, Rows, Cols> ColumnListIterator<Number, Rows, Cols>::operator++() {
    _idx += 1;
    return *this;
}

template<class Number, std::size_t Rows, std::size_t Cols>
bool ColumnListIterator<Number, Rows, Cols>::operator!=(ColumnListIterator other) {
    return _idx != other._idx;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Column<Number, Rows, Cols> ColumnListIterator<Number, Rows, Cols>::operator*() const {
    return _matrix.column(_idx);
}


template<class Number, std::size_t Rows, std::size_t Cols>
ColumnList<Number, Rows, Cols>::ColumnList(typename std::array<Number, Rows * Cols>& initial):
    _matrix{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>
ColumnListIterator<Number, Rows, Cols> ColumnList<Number, Rows, Cols>::begin() {
    return ColumnListIterator(_matrix, 0);
}

template<class Number, std::size_t Rows, std::size_t Cols>
ColumnListIterator<Number, Rows, Cols> ColumnList<Number, Rows, Cols>::end() {
    return ColumnListIterator(_matrix, Cols);
}


template<class Number, std::size_t Rows, std::size_t Cols>
RowListIterator<Number, Rows, Cols>::RowListIterator(typename std::array<Number, Rows * Cols>& initial, std::size_t idx):
    _idx{idx},
    _matrix{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>    
RowListIterator<Number, Rows, Cols> RowListIterator<Number, Rows, Cols>::operator++() {
    _idx += 1;
    return *this;
}

template<class Number, std::size_t Rows, std::size_t Cols>
bool RowListIterator<Number, Rows, Cols>::operator!=(RowListIterator other) {
    return _idx != other._idx;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Row<Number, Rows, Cols> RowListIterator<Number, Rows, Cols>::operator*() const {
    return Row<Number, Rows, Cols>(_matrix, _idx);
}


template<class Number, std::size_t Rows, std::size_t Cols>
RowList<Number, Rows, Cols>::RowList(typename std::array<Number, Rows * Cols>& initial):
    _matrix{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>
RowListIterator<Number, Rows, Cols> RowList<Number, Rows, Cols>::begin() {
    return RowListIterator<Number, Rows, Cols>(_matrix, 0);
}

template<class Number, std::size_t Rows, std::size_t Cols>
RowListIterator<Number, Rows, Cols> RowList<Number, Rows, Cols>::end() {
    return RowListIterator<Number, Rows, Cols>(_matrix, Rows);
}