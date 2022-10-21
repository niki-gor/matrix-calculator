#pragma once

#include "matrix.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(){}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(std::array<Number, Rows * Cols> initial):
    storage{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>
typename std::array<Number, Rows * Cols>::iterator Matrix<Number, Rows, Cols>::begin() {
    return storage.begin();
}

template<class Number, std::size_t Rows, std::size_t Cols>
typename std::array<Number, Rows * Cols>::iterator Matrix<Number, Rows, Cols>::end() {
    return storage.end();
}

template<class Number, std::size_t Rows, std::size_t Cols>
Column<Number, Rows, Cols> Matrix<Number, Rows, Cols>::column(std::size_t idx) {
    return Column<Number, Rows, Cols>(storage, idx);
}

template<class Number, std::size_t Rows, std::size_t Cols>
Row<Number, Rows, Cols> Matrix<Number, Rows, Cols>::row(std::size_t idx) {
    return Row<Number, Rows, Cols>(storage, idx);
}

template<class Number, std::size_t Rows, std::size_t Cols>
ColumnList<Number, Rows, Cols> Matrix<Number, Rows, Cols>::columns() {
    return ColumnList<Number, Rows, Cols>(storage);
}

template<class Number, std::size_t Rows, std::size_t Cols>
RowList<Number, Rows, Cols> Matrix<Number, Rows, Cols>::rows() {
    return RowList<Number, Rows, Cols>(storage);
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator-() {
    Matrix<Number, Rows, Cols> result;
    std::transform(begin(), end(), result.begin(), [](Number elem) {return -elem;});
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
void Matrix<Number, Rows, Cols>::operator+=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem + val;});
}

template<class Number, std::size_t Rows, std::size_t Cols>
void Matrix<Number, Rows, Cols>::operator-=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem - val;});
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator+(Number val) {
    Matrix<Number, Rows, Cols> result = *this;
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem + val;});
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator-(Number val) {
    Matrix<Number, Rows, Cols> result = *this;
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem - val;});
}

template<class Number, std::size_t Rows, std::size_t Cols>
void Matrix<Number, Rows, Cols>::operator+=(Matrix<Number, Rows, Cols>& other) {
    std::transform(begin(), end(), other.begin(), begin(), std::plus<>{});
}

template<class Number, std::size_t Rows, std::size_t Cols>
void Matrix<Number, Rows, Cols>::operator-=(Matrix<Number, Rows, Cols>& other) {
    std::transform(begin(), end(), other.begin(), begin(), std::minus<>{});
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator+(Matrix<Number, Rows, Cols> other) {
    return other += *this;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator-(Matrix<Number, Rows, Cols> other) {
    return other -= *this;
}
