#pragma once

#include <algorithm>

#include "matrix.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(){}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(std::array<Number, Rows * Cols> initial):
    _storage{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>
SliceIterator<Number> Matrix<Number, Rows, Cols>::begin() {
    return SliceIterator<Number>(_storage.begin(), 1);
}

template<class Number, std::size_t Rows, std::size_t Cols>
SliceIterator<Number> Matrix<Number, Rows, Cols>::end() {
    return SliceIterator<Number>(_storage.end(), 1);
}

template<class Number, std::size_t Rows, std::size_t Cols>
Slice<Number, Rows> Matrix<Number, Rows, Cols>::column(std::size_t idx) {
    return Slice<Number, Rows>(_storage.begin() + idx, Cols);
}

template<class Number, std::size_t Rows, std::size_t Cols>
Slice<Number, Cols> Matrix<Number, Rows, Cols>::row(std::size_t idx) {
    return Slice<Number, Cols>(_storage.begin() + Cols * idx, 1);
}

template<class Number, std::size_t Rows, std::size_t Cols>
Generator<Slice<Number, Rows>, Cols> Matrix<Number, Rows, Cols>::columns() {
    return Generator<Slice<Number, Rows>, Cols>([this](std::size_t idx) {
        return Slice<Number, Rows>(_storage.begin() + idx, Cols);
    });
}

template<class Number, std::size_t Rows, std::size_t Cols>
Generator<Slice<Number, Cols>, Rows> Matrix<Number, Rows, Cols>::rows() {
    return Generator<Slice<Number, Cols>, Rows>([this](std::size_t idx) {
        return Slice<Number, Cols>(_storage.begin() + idx * Cols, 1);
    });
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
void Matrix<Number, Rows, Cols>::operator*=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem * val;});
}

template<class Number, std::size_t Rows, std::size_t Cols>
void Matrix<Number, Rows, Cols>::operator/=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem / val;});
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator+(Number val) {
    Matrix<Number, Rows, Cols> result;
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem + val;});
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator-(Number val) {
    Matrix<Number, Rows, Cols> result;
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem - val;});
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator*(Number val) {
    Matrix<Number, Rows, Cols> result;
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem * val;});
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator/(Number val) {
    Matrix<Number, Rows, Cols> result;
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem / val;});
    return result;
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

template<class Number, std::size_t Rows, std::size_t Cols>
template<std::size_t SecondCols>
Matrix<Number, Rows, SecondCols> Matrix<Number, Rows, Cols>::operator*(Matrix<Number, Cols, SecondCols>& other) {
    Matrix<Number, Rows, SecondCols> result;
    SliceIterator<Number> iter = result.begin();
    for (Slice<Number, Cols> row : rows()) {
        for (Slice<Number, Cols> column : other.columns()) {
            *iter = row * column;
            ++iter;
        }
    }
    return result;
}