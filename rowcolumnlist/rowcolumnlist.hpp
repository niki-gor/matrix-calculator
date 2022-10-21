#pragma once

#include <array>

#include "rowcolumn.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnListIterator {
private:
    typename std::array<Number, Rows * Cols>& _matrix;
    std::size_t _idx;
public:
    ColumnListIterator(typename std::array<Number, Rows * Cols>& initial, std::size_t idx);
        
    ColumnListIterator<Number, Rows, Cols> operator++();

    bool operator!=(ColumnListIterator other);

    Column<Number, Rows, Cols> operator*() const;
};


template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnList {
private:
    typename std::array<Number, Rows * Cols>& _matrix;
public:
    ColumnList(typename std::array<Number, Rows * Cols>& initial);

    ColumnListIterator<Number, Rows, Cols> begin();

    ColumnListIterator<Number, Rows, Cols> end();
};


template<class Number, std::size_t Rows, std::size_t Cols>
class RowListIterator {
private:
    typename std::array<Number, Rows * Cols>& _matrix;
    std::size_t _idx;
public:
    RowListIterator(typename std::array<Number, Rows * Cols>& initial, std::size_t idx);
        
    RowListIterator<Number, Rows, Cols> operator++();

    bool operator!=(RowListIterator other);

    Row<Number, Rows, Cols> operator*() const;
};


template<class Number, std::size_t Rows, std::size_t Cols>
class RowList {
private:
    typename std::array<Number, Rows * Cols>& _matrix;
public:
    RowList(typename std::array<Number, Rows * Cols>& initial);

    RowListIterator<Number, Rows, Cols> begin();

    RowListIterator<Number, Rows, Cols> end();
};

// зачем? потому что для темлейтов нужно "прогонять" код два раза, чтобы все было ок
// поэтому нужно либо писать определение шаблона там же, где и описание
// либо делать так, как здесь
#include "rowcolumnlist.cpp"