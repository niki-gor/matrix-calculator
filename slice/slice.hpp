#pragma once

#include <array>
#include <numeric>
#include <stdexcept>
#include <algorithm>
#include <memory>


template<class Number>
class SliceIterator {
private:
    Number* _iterator;
    std::size_t _step;
public:
    SliceIterator(Number* start, std::size_t step);

    SliceIterator<Number> operator++();

    SliceIterator<Number> operator+(std::size_t shift);

    bool operator==(SliceIterator<Number> other);

    Number& operator*() const;
};


template<class Number, std::size_t Len>
class Slice {
private:
    std::shared_ptr<std::array<Number, Len>> _allocated;
    Number* _begin;
    std::size_t _step;

public:
    Slice(Number* start, std::size_t step);

    Slice(std::array<Number, Len> initial);

    Slice(const Slice<Number, Len>& other);

    Slice<Number, Len> copy();
    
    SliceIterator<Number> begin();

    SliceIterator<Number> end();

    Number operator*(Slice<Number, Len> other);

    void operator+=(Slice<Number, Len> other);

    void operator-=(Slice<Number, Len> other);

    void operator+=(Number val);

    void operator-=(Number val);

    void operator*=(Number val);

    void operator/=(Number val);


    Slice<Number, Len> operator+(Slice<Number, Len> other);

    Slice<Number, Len> operator-(Slice<Number, Len> other);

    Slice<Number, Len> operator+(Number val);

    Slice<Number, Len> operator-(Number val);

    Slice<Number, Len> operator*(Number val);

    Slice<Number, Len> operator/(Number val);
    

    Number& operator[](std::size_t idx);
};


#include "slice.cpp"