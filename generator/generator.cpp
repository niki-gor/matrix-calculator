#pragma once

#include <functional>
#include <stdexcept>

#include "generator.hpp"


template<class Number>
GeneratorIterator<Number>::GeneratorIterator(std::function<Number(std::size_t)> generator, std::size_t start):
    _generator{generator},
    _index{start} {}

template<class Number>
GeneratorIterator<Number> GeneratorIterator<Number>::operator++() {
    ++_index;
    return *this;
}

template<class Number>
GeneratorIterator<Number> GeneratorIterator<Number>::operator+(std::size_t shift) {
    return GeneratorIterator<Number>(_generator, _index + shift);
}


template<class Number>
bool GeneratorIterator<Number>::operator==(GeneratorIterator<Number> other) {
    return _index == other._index;
}

template<class Number>
Number GeneratorIterator<Number>::operator*() const {
    return _generator(_index);
}


template<class Number, std::size_t Len>
Generator<Number, Len>::Generator(std::function<Number(std::size_t)> generator):
    _generator{generator} {}

template<class Number, std::size_t Len>
GeneratorIterator<Number> Generator<Number, Len>::begin() {
    return GeneratorIterator(_generator, 0);
}

template<class Number, std::size_t Len>
GeneratorIterator<Number> Generator<Number, Len>::end() {
    return GeneratorIterator(_generator, Len);
}