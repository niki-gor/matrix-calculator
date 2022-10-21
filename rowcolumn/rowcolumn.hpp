#pragma once

#include <array>
#include <algorithm>
#include <stdexcept>


template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnIterator {
private:
    typename std::array<Number, Rows * Cols>::iterator _iterator;
public:
    ColumnIterator(typename std::array<Number, Rows * Cols>::iterator iterator);

    ColumnIterator<Number, Rows, Cols> operator++();

    bool operator!=(ColumnIterator other);

    Number& operator*() const;
};


template<class Number, std::size_t Rows, std::size_t Cols>
class Column {
private:
    typename std::array<Number, Rows * Cols>::iterator _begin;
    typename std::array<Number, Rows * Cols>::iterator _end;

public:
    Column(typename std::array<Number, Rows * Cols>& initial, std::size_t idx);
    
    ColumnIterator<Number, Rows, Cols> begin();

    ColumnIterator<Number, Rows, Cols> end();

    std::array<Number, Rows> copy();
};









template<class Number, std::size_t Rows, std::size_t Cols>
class RowIterator {
private:
    typename std::array<Number, Rows * Cols>::iterator _iterator;
public:
    RowIterator(typename std::array<Number, Rows * Cols>::iterator iterator);

    RowIterator<Number, Rows, Cols> operator++();

    bool operator!=(RowIterator other);

    Number& operator*() const;
};


template<class Number, std::size_t Rows, std::size_t Cols>
class Row {
private:
    typename std::array<Number, Rows * Cols>::iterator _begin;
    typename std::array<Number, Rows * Cols>::iterator _end;

public:
    Row(typename std::array<Number, Rows * Cols>& initial, std::size_t idx);
    
    RowIterator<Number, Rows, Cols> begin();

    RowIterator<Number, Rows, Cols> end();

    std::array<Number, Cols> copy();
};


#include "rowcolumn.cpp"