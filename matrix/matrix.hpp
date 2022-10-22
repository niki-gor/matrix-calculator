#pragma once

#include <array>
#include <stdexcept>
#include <algorithm>

#include "slice.hpp"
#include "generator.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
class Matrix {
private:
    typename std::array<Number, Rows * Cols> _storage;
public:
    Matrix();

    Matrix(std::array<Number, Rows * Cols> initial);
    
    SliceIterator<Number> begin();

    SliceIterator<Number> end();

    Slice<Number, Rows> column(std::size_t idx);

    Slice<Number, Cols> row(std::size_t idx);

    Slice<Number, Cols> operator[](std::size_t idx);

    Generator<Slice<Number, Rows>, Cols> columns();

    Generator<Slice<Number, Cols>, Rows> rows();

    Matrix<Number, Rows, Cols> operator-();

    void operator+=(Number val);

    void operator-=(Number val);

    void operator*=(Number val);

    void operator/=(Number val);

    Matrix<Number, Rows, Cols> operator+(Number val);

    Matrix<Number, Rows, Cols> operator-(Number val);

    Matrix<Number, Rows, Cols> operator*(Number val);

    Matrix<Number, Rows, Cols> operator/(Number val);

    void operator+=(Matrix<Number, Rows, Cols>& other);

    void operator-=(Matrix<Number, Rows, Cols>& other);

    Matrix<Number, Rows, Cols> operator+(Matrix<Number, Rows, Cols> other);

    Matrix<Number, Rows, Cols> operator-(Matrix<Number, Rows, Cols> other);

    template<std::size_t SecondCols>
    Matrix<Number, Rows, SecondCols> operator*(Matrix<Number, Cols, SecondCols>& other);

    Matrix<Number, Cols, Rows> transposed();
};


#include "matrix.cpp"