#pragma once

#include "matrix.hpp"


template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(){}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(std::array<Number, Rows * Cols> initial):
    _storage{initial} {}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols>::Matrix(const Matrix<Number, Rows, Cols>& other):
    _storage{other._storage} {}

template<class Number, std::size_t Rows, std::size_t Cols>
bool Matrix<Number, Rows, Cols>::operator==(Matrix<Number, Rows, Cols> other) const {
    return _storage == other._storage;
}

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
    std::transform(begin(), end(), other.begin(), other.begin(), std::plus<>{});
    return other;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Rows, Cols> Matrix<Number, Rows, Cols>::operator-(Matrix<Number, Rows, Cols> other) {
    std::transform(begin(), end(), other.begin(), other.begin(), std::minus<>{});
    return other;
}

template<class Number, std::size_t Rows, std::size_t Cols>
template<std::size_t SecondCols>
Matrix<Number, Rows, SecondCols> Matrix<Number, Rows, Cols>::operator*(Matrix<Number, Cols, SecondCols>& other) {
    Matrix<Number, Rows, SecondCols> result;
    auto iter = result.begin();
    for (auto row : rows()) {
        for (auto column : other.columns()) {
            *iter = row * column;
            ++iter;
        }
    }
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Matrix<Number, Cols, Rows> Matrix<Number, Rows, Cols>::transposed() {
    Matrix<Number, Cols, Rows> result;
    auto row = result.rows().begin();
    for (auto col : columns()) {
        std::transform(col.begin(), col.end(), (*row).begin(), [](Number elem) {return elem;});
        ++row;
    }
    return result;
}

template<class Number, std::size_t Rows, std::size_t Cols>
Slice<Number, std::min(Rows, Cols)> Matrix<Number, Rows, Cols>::main_diagonal() {
    return Slice<Number, std::min(Rows, Cols)>(_storage.begin(), Cols + 1);
}

template<class Number, std::size_t Rows, std::size_t Cols>
Slice<Number, Cols> Matrix<Number, Rows, Cols>::operator[](std::size_t row_idx) {
    return row(row_idx);
}

template<class Number, std::size_t N>
double det(Matrix<Number, N, N>& m) {
    std::array<double, N * N> storage;
    std::transform(m.begin(), m.end(), storage.begin(), [](Number val) {return double(val);});
    Matrix<double, N, N> matrix(storage);

    auto rows = matrix.rows();
    for (std::size_t idx = 0; idx < N; ++idx) {
        auto row = rows.begin() + idx;
        auto not_null_row = row;
        while (not_null_row != rows.end() && (*not_null_row)[idx] == 0) {
            ++not_null_row;
        }
        if (not_null_row == rows.end()) {
            return 0;
        }
        std::swap_ranges((*row).begin(), (*row).end(), (*not_null_row).begin());
        auto make_null_row = row;
        for (++make_null_row; make_null_row != rows.end(); ++make_null_row) {
            double k = (*make_null_row)[idx] / (*row)[idx];
            *make_null_row -= *row * k;
        }
    }
    auto diagonal = matrix.main_diagonal();
    return std::accumulate(diagonal.begin(), diagonal.end(), 1.0, std::multiplies<double>());
}
