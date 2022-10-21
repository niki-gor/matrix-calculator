#pragma once

#include "slice.hpp"


template<class Number>
SliceIterator<Number>::SliceIterator(Number* start, std::size_t step):
    _iterator{start},
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
