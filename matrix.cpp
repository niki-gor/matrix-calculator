#include <array>
#include <stdexcept>
#include <tuple>
#include <algorithm>

#include <valarray>



template<class Number, std::size_t Rows, std::size_t Cols>
class Column;

template<class Number, std::size_t Rows, std::size_t Cols>
class Row;

template<class Number, std::size_t Rows, std::size_t Cols>
class Matrix;

template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnListIterator;

template<class Number, std::size_t Rows, std::size_t Cols>
class RowListIterator;





template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnList {
private:
    Matrix<Number, Rows, Cols>& _matrix;
public:
    ColumnList(Matrix<Number, Rows, Cols>& initial):
        _matrix{initial} {}

    ColumnListIterator<Number, Rows, Cols> begin() {
        return ColumnListIterator(_matrix, 0);
    }

    ColumnListIterator<Number, Rows, Cols> end() {
        return ColumnListIterator(_matrix, Cols);
    }
};

template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnListIterator {
private:
    Matrix<Number, Rows, Cols>& _matrix;
    std::size_t _idx;
public:
    ColumnListIterator(Matrix<Number, Rows, Cols>& initial, std::size_t idx):
        _idx{idx},
        _matrix{initial} {}
        
    ColumnListIterator<Number, Rows, Cols> operator++() {
        _idx += 1;
        return *this;
    }

    bool operator!=(ColumnListIterator other) {
        return _idx != other._idx;
    }

    Column<Number, Rows, Cols> operator*() const {
        return _matrix.column(_idx);
    }
};




template<class Number, std::size_t Rows, std::size_t Cols>
class RowList {
private:
    Matrix<Number, Rows, Cols>& _matrix;
public:
    RowList(Matrix<Number, Rows, Cols>& initial):
        _matrix{initial} {}

    RowListIterator<Number, Rows, Cols> begin() {
        return RowListIterator(_matrix, 0);
    }

    RowListIterator<Number, Rows, Cols> end() {
        return RowListIterator(_matrix, Rows);
    }
};

template<class Number, std::size_t Rows, std::size_t Cols>
class RowListIterator {
private:
    Matrix<Number, Rows, Cols>& _matrix;
    std::size_t _idx;
public:
    RowListIterator(Matrix<Number, Rows, Cols>& initial, std::size_t idx):
        _idx{idx},
        _matrix{initial} {}
        
    RowListIterator<Number, Rows, Cols> operator++() {
        _idx += 1;
        return *this;
    }

    bool operator!=(RowListIterator other) {
        return _idx != other._idx;
    }

    Row<Number, Rows, Cols> operator*() const {
        return _matrix.row(_idx);
    }
};









template<class Number, std::size_t Rows, std::size_t Cols>
class Matrix {
private:
    typename std::array<Number, Rows * Cols> storage;
public:
    Matrix(){}

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

    ColumnList<Number, Rows, Cols> columns() {
        return ColumnList(*this);
    }

    RowList<Number, Rows, Cols> rows() {
        return RowList(*this);
    }

    Matrix<Number, Rows, Cols> operator-() {
        Matrix<Number, Rows, Cols> result;
        std::transform(begin(), end(), result.begin(), [](Number elem) {return -elem;});
        return result;
    }

    void operator+=(Number val) {
        std::transform(begin(), end(), begin(), [val](Number elem) {return elem + val;});
    }

    void operator-=(Number val) {
        std::transform(begin(), end(), begin(), [val](Number elem) {return elem - val;});
    }

    Matrix<Number, Rows, Cols> operator+(Number val) {
        Matrix<Number, Rows, Cols> result = *this;
        std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem + val;});
    }

    void operator+=(Matrix<Number, Rows, Cols>& other) {
        std::transform(begin(), end(), other.begin(), begin(), std::plus<>{});
    }

    void operator-=(Matrix<Number, Rows, Cols>& other) {
        std::transform(begin(), end(), other.begin(), begin(), std::minus<>{});
    }

    Matrix<Number, Rows, Cols> operator+(Matrix<Number, Rows, Cols> other) {
        return other += *this;
    }

    Matrix<Number, Rows, Cols> operator-(Matrix<Number, Rows, Cols> other) {
        return other += *this;
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
        std::copy(begin(), end(), result.begin());
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

    Number& operator*() const {
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

    std::array<Number, Cols> copy() {
        std::array<Number, Cols> result;
        for (auto iter = result.begin(); auto& elem : *this) {
            *iter++ = elem;
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

    Number& operator*() const {
        return *_iterator;
    }
};







#include <iostream>

int main() {
    Matrix<int, 2, 3> m({
        3, 4, 7,
        1, 2, 3
    });

    auto c = m.row(1).copy();
    for (auto& i : c) {
        std::cout << i << ' ';
    }

    m = -m;

    for (auto row : m.rows()) {
        for (auto elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}