#pragma once

#include <array>
#include <stdexcept>
#include <algorithm>

#include "rowcolumn.hpp"
#include "rowcolumnlist.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
class Matrix {
private:
    typename std::array<Number, Rows * Cols> storage;
public:
    Matrix();

    Matrix(std::array<Number, Rows * Cols> initial);
    
    typename std::array<Number, Rows * Cols>::iterator begin();

    typename std::array<Number, Rows * Cols>::iterator end();

    Column<Number, Rows, Cols> column(std::size_t idx);

    Row<Number, Rows, Cols> row(std::size_t idx);

    ColumnList<Number, Rows, Cols> columns();

    RowList<Number, Rows, Cols> rows();

    Matrix<Number, Rows, Cols> operator-();

    void operator+=(Number val);

    void operator-=(Number val);

    Matrix<Number, Rows, Cols> operator+(Number val);

    Matrix<Number, Rows, Cols> operator-(Number val);

    void operator+=(Matrix<Number, Rows, Cols>& other);

    void operator-=(Matrix<Number, Rows, Cols>& other);

    Matrix<Number, Rows, Cols> operator+(Matrix<Number, Rows, Cols> other);

    Matrix<Number, Rows, Cols> operator-(Matrix<Number, Rows, Cols> other);
};


#include "matrix.cpp"