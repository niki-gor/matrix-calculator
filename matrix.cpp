#include <array>
#include <stdexcept>


template<class Number, std::size_t Rows, std::size_t Cols>
class Column;

template<class Number, std::size_t Rows, std::size_t Cols>
class Row;


template<class Number, std::size_t Rows, std::size_t Cols>
class Matrix {
private:
    typename std::array<Number, Rows * Cols> storage;
public:
    Matrix() {
        storage.fill(0);
    }

    Matrix(std::array<Number, Rows * Cols> initial):
        storage{initial} {}

    typename std::array<Number, Rows * Cols>::iterator begin() {
        return storage.begin();
    }

    typename std::array<Number, Rows * Cols>::iterator end() {
        return storage.end();
    }

    Column<Number, Rows, Cols> column(std::size_t idx) {
        return Column(*this, idx);
    }

    Row<Number, Rows, Cols> row(std::size_t idx) {
        return Row(*this, idx);
    }
};


template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnIterator;


template<class Number, std::size_t Rows, std::size_t Cols>
class Column {
private:
    typename std::array<Number, Rows * Cols>::iterator _begin;
    typename std::array<Number, Rows * Cols>::iterator _end;

public:
    Column(Matrix<Number, Rows, Cols>& initial, std::size_t idx):
        _begin{initial.begin() + idx},
        _end{initial.begin() + idx + Rows * Cols} 
    {
        if (idx >= Cols) {
            throw std::invalid_argument("column idx out of boundaries");
        }
    }
    
    ColumnIterator<Number, Rows, Cols> begin() {
        return ColumnIterator<Number, Rows, Cols>(_begin);
    }

    ColumnIterator<Number, Rows, Cols> end() {
        return ColumnIterator<Number, Rows, Cols>(_end);
    }

    std::array<Number, Rows> copy() {
        std::array<Number, Rows> result;
        auto resultIterator = result.begin();
        for (auto i : *this) {
            *resultIterator++ = i;
        }
        return result;
    }
};


template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnIterator {
private:
    typename std::array<Number, Rows * Cols>::iterator _iterator;
public:
    ColumnIterator(typename std::array<Number, Rows * Cols>::iterator iterator):
        _iterator{iterator} {}

    ColumnIterator<Number, Rows, Cols> operator++() {
        _iterator += Cols;
        return *this;
    }

    bool operator!=(ColumnIterator other) {
        return _iterator != other._iterator;
    }

    const Number& operator*() const {
        return *_iterator;
    }
};









template<class Number, std::size_t Rows, std::size_t Cols>
class RowIterator;


template<class Number, std::size_t Rows, std::size_t Cols>
class Row {
private:
    typename std::array<Number, Rows * Cols>::iterator _begin;
    typename std::array<Number, Rows * Cols>::iterator _end;

public:
    Row(Matrix<Number, Rows, Cols>& initial, std::size_t idx):
        _begin{initial.begin() + Cols * idx},
        _end{initial.begin() + Cols * idx + Cols} 
    {
        if (idx >= Rows) {
            throw std::invalid_argument("row idx out of boundaries");
        }
    }
    
    RowIterator<Number, Rows, Cols> begin() {
        return RowIterator<Number, Rows, Cols>(_begin);
    }

    RowIterator<Number, Rows, Cols> end() {
        return RowIterator<Number, Rows, Cols>(_end);
    }

    std::array<Number, Rows> copy() {
        std::array<Number, Rows> result;
        auto resultIterator = result.begin();
        for (auto i : *this) {
            *resultIterator++ = i;
        }
        return result;
    }
};


template<class Number, std::size_t Rows, std::size_t Cols>
class RowIterator {
private:
    typename std::array<Number, Rows * Cols>::iterator _iterator;
public:
    RowIterator(typename std::array<Number, Rows * Cols>::iterator iterator):
        _iterator{iterator} {}

    RowIterator<Number, Rows, Cols> operator++() {
        _iterator += 1;
        return *this;
    }

    bool operator!=(RowIterator other) {
        return _iterator != other._iterator;
    }

    const Number& operator*() const {
        return *_iterator;
    }
};






#include <iostream>

int main() {
    Matrix<int, 2, 3> lol({
        1, 2, 3,
        4, 5, 6
    });
    auto c = lol.column(2).copy();
    for (auto& i : c) {
        std::cout << i << '\n';
    }

    auto r = lol.row(0);
    for (auto& i : r) {
        std::cout << i << ' ';
    }
}