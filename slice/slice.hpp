#pragma once

#include <array>
#include <numeric>
#include <stdexcept>


template<class Number>
class SliceIterator {
protected:
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
    Number* _begin;
    std::size_t _step;

public:
    Slice(Number* start, std::size_t step);
    
    SliceIterator<Number> begin();

    SliceIterator<Number> end();

    Number operator*(Slice<Number, Len> other);

    void operator+=(Slice<Number, Len> other);

    void operator-=(Slice<Number, Len> other);

    void operator*=(Number val);

    Number& operator[](std::size_t idx);
};


#include "slice.cpp"