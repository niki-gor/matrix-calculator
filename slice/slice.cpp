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
SliceIterator<Number> SliceIterator<Number>::operator+(std::size_t shift) {
    return SliceIterator<Number>(_iterator + _step * shift, _step);
}

template<class Number>
bool SliceIterator<Number>::operator==(SliceIterator<Number> other) {
    return _iterator == other._iterator;
}

template<class Number>
Number& SliceIterator<Number>::operator*() const {
    return *_iterator;
}


template<class Number, std::size_t Len>
Slice<Number, Len>::Slice(Number* begin, std::size_t step):
    _allocated{nullptr},
    _begin{begin},
    _step{step} {}

template<class Number, std::size_t Len>
Slice<Number, Len>::Slice(std::array<Number, Len> initial):
    _allocated{std::make_shared<std::array<Number, Len>>(std::move(initial))},
    _begin{_allocated->begin()},
    _step{1} {}

template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::copy() {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), result.begin(), [](Number elem) {return elem;});
    return result;
}

template<class Number, std::size_t Len>
bool Slice<Number, Len>::operator==(Slice<Number, Len> other) const {
    return std::equal(begin(), end(), other.begin());
}

template<class Number, std::size_t Len>
SliceIterator<Number> Slice<Number, Len>::begin() const {
    return SliceIterator<Number>(_begin, _step);
}

template<class Number, std::size_t Len>
SliceIterator<Number> Slice<Number, Len>::end() const {
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
void Slice<Number, Len>::operator+=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem + val;});
}

template<class Number, std::size_t Len>
void Slice<Number, Len>::operator-=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem - val;});
}

template<class Number, std::size_t Len>
void Slice<Number, Len>::operator*=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem * val;});
}

template<class Number, std::size_t Len>
void Slice<Number, Len>::operator/=(Number val) {
    std::transform(begin(), end(), begin(), [val](Number elem) {return elem / val;});
}


template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::operator+(Slice<Number, Len> other) {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), other.begin(), result.begin(), std::plus<>{});
    return result;
}

template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::operator-(Slice<Number, Len> other) {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), other.begin(), result.begin(), std::minus<>{});
    return result;
}

template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::operator+(Number val) {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem + val;});   
    return result;
}

template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::operator-(Number val) {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem - val;});
    return result;
}

template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::operator*(Number val) {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem * val;});
    return result;
}

template<class Number, std::size_t Len>
Slice<Number, Len> Slice<Number, Len>::operator/(Number val) {
    Slice<Number, Len> result(std::array<Number, Len>{});
    std::transform(begin(), end(), result.begin(), [val](Number elem) {return elem / val;});
    return result;
}


template<class Number, std::size_t Len>
Number& Slice<Number, Len>::operator[](std::size_t idx) {
    return _begin[_step * idx];
}