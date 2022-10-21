#pragma once

#include <array>
#include <algorithm>
#include <stdexcept>


template<class Number>
class SliceIterator {
private:
    Number* _iterator;
    std::size_t _step;
public:
    SliceIterator(Number* start, std::size_t step);

    SliceIterator<Number> operator++();

    bool operator!=(SliceIterator<Number> other);

    Number& operator*() const;
};


template<class Number, std::size_t Len>
class Slice {
private:
    Number* _start;
    std::size_t step;

public:
    Slice(Number* start, std::size_t step);
    
    SliceIterator<Number> begin();

    SliceIterator<Number> end();

    std::array<Number, Len> copy();

    Number operator*(Slice<Number, Len> other);
};


#include "slice.cpp"