#include <array>
#include <stdexcept>


template<class T>
concept Rangeable = requires(T val) {
    val.begin();
    val.end();
};


template<class T>
concept Iterable = requires(T val) {
    *val;
    ++val;
    val != val;
};

template<class Range, class Iterator> requires Rangeable<Range> && Iterable<Iterator>
class ZippedIterator {
private:
    Iterator _first;
    Iterator _second;
public:
    ZippedIterator(Iterator first, Iterator second):
        _first{first}, 
        _second{second} {}

    ZippedIterator<Range, Iterator> operator++() {
        ++_first;
        ++_second;
        return *this;
    }

    bool operator!=(ZippedIterator<Range, Iterator> other) {
        return *this != other;
    }

    template<class Storaged>
    const std::tuple<Storaged, Storaged>& operator*() {
        return std::tuple{*_first, *_second};
    }
};

template<class Range> requires Rangeable<Range>
class ZippedRange {
private:
    Range _first;
    Range _second;
public:
    ZippedRange(Range first, Range second):
        _first{first},
        _second{second} {}
    
    template<class Iterator> requires Iterable<Iterator>
    ZippedIterator<Range, Iterator> begin() {
        return ZippedIterator<Range, Iterator>(_first.begin(), _second.begin());
    }

    template<class Iterator> requires Iterable<Iterator>
    ZippedIterator<Range, Iterator> end() {
        return ZippedIterator<Range, Iterator>(_first.end(), _second.end());
    }
};

template<class Range> requires Rangeable<Range>
ZippedRange<Range> zip(Range first, Range second) {
    return ZippedRange<Range>(first, second);
}




template<class Number, std::size_t Rows, std::size_t Cols>
class Column;

template<class Number, std::size_t Rows, std::size_t Cols>
class Row;

template<class Number, std::size_t Rows, std::size_t Cols>
class Matrix;

template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnSIterator;

template<class Number, std::size_t Rows, std::size_t Cols>
class RowSIterator;










template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnS {
private:
    Matrix<Number, Rows, Cols>& _matrix;
public:
    ColumnS(Matrix<Number, Rows, Cols>& initial):
        _matrix{initial} {}

    ColumnSIterator<Number, Rows, Cols> begin() {
        return ColumnSIterator(_matrix, 0);
    }

    ColumnSIterator<Number, Rows, Cols> end() {
        return ColumnSIterator(_matrix, Cols);
    }
};

template<class Number, std::size_t Rows, std::size_t Cols>
class ColumnSIterator {
private:
    Matrix<Number, Rows, Cols>& _matrix;
    std::size_t _idx;
public:
    ColumnSIterator(Matrix<Number, Rows, Cols>& initial, std::size_t idx):
        _idx{idx},
        _matrix{initial} {}
        
    ColumnSIterator<Number, Rows, Cols> operator++() {
        _idx += 1;
        return *this;
    }

    bool operator!=(ColumnSIterator other) {
        return _idx != other._idx;
    }

    Column<Number, Rows, Cols> operator*() const {
        return _matrix.column(_idx);
    }
};




template<class Number, std::size_t Rows, std::size_t Cols>
class RowS {
private:
    Matrix<Number, Rows, Cols>& _matrix;
public:
    RowS(Matrix<Number, Rows, Cols>& initial):
        _matrix{initial} {}

    RowSIterator<Number, Rows, Cols> begin() {
        return RowSIterator(_matrix, 0);
    }

    RowSIterator<Number, Rows, Cols> end() {
        return RowSIterator(_matrix, Rows);
    }
};

template<class Number, std::size_t Rows, std::size_t Cols>
class RowSIterator {
private:
    Matrix<Number, Rows, Cols>& _matrix;
    std::size_t _idx;
public:
    RowSIterator(Matrix<Number, Rows, Cols>& initial, std::size_t idx):
        _idx{idx},
        _matrix{initial} {}
        
    RowSIterator<Number, Rows, Cols> operator++() {
        _idx += 1;
        return *this;
    }

    bool operator!=(RowSIterator other) {
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

    ColumnS<Number, Rows, Cols> columns() {
        return ColumnS(*this);
    }

    RowS<Number, Rows, Cols> rows() {
        return RowS(*this);
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

    Number& operator*() const {
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

    std::cout << "\n\n";
    for (auto column : lol.columns()) {
        for (auto elem : column) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

    *lol.row(1).begin() = 7; 

    std::cout << '\n';

    for (auto column : lol.columns()) {
        for (auto elem : column) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

    *lol.row(2).begin() = 1337;

    std::cout << "\n\n";

    for (auto row : lol.rows()) {
        for (auto& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

    for (auto [first, second] : zip(lol.row(1), lol.row(2))) {
        std::cout << first << ' ' << second << '\n';
    }
}