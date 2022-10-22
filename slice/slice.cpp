#pragma once

#include "slice.hpp"


template<class Number>
SliceIterator<Number>::SliceIterator(Number* initial, std::size_t step):
    _iterator{initial},
    _step{step} {}

template<class Number>
SliceIterator<Number> SliceIterator<Number>::operator++() {
    _iterator += _step;
    return *this;
}

template<class Number>
bool SliceIterator<Number>::operator!=(SliceIterator<Number> other) {
    return _iterator != other._iterator;
}

template<class Number>
Number& SliceIterator<Number>::operator*() const {
    return *_iterator;
}


template<class Number, std::size_t Len>
Slice<Number, Len>::Slice(Number* begin, std::size_t step):
    _begin{begin},
    _step{step} {}

template<class Number, std::size_t Len>
SliceIterator<Number> Slice<Number, Len>::begin() {
    return SliceIterator<Number>(_begin, _step);
}

template<class Number, std::size_t Len>
SliceIterator<Number> Slice<Number, Len>::end() {
    return SliceIterator<Number>(_begin + _step * Len, _step);
}

template<class Number, std::size_t Len>
Number Slice<Number, Len>::operator*(Slice<Number, Len> other) {
    return std::inner_product(begin(), end(), other.begin(), 0);
}

template<class Number, std::size_t Len>
void Slice<Number, Len>::operator+=(Slice<Number, Len> other) {
    std::transform(begin(), end(), other.begin(), begin(), std::plus<>{});
}

template<class Number, std::size_t Len>
void Slice<Number, Len>::operator-=(Slice<Number, Len> other) {
    std::transform(begin(), end(), other.begin(), begin(), std::minus<>{});
}

template<class Number, std::size_t Len>
Number& Slice<Number, Len>::operator[](std::size_t idx) {
    return _begin[idx];
}