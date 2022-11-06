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
    using difference_type = std::ptrdiff_t;
    using value_type = Number;
    using pointer = Number*;
    using reference = Number&;
    using iterator_category = std::random_access_iterator_tag;

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

    bool operator==(Slice<Number, Len> other) const;
    
    SliceIterator<Number> begin() const;

    SliceIterator<Number> end() const;

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