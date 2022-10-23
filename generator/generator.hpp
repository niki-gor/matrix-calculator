#pragma once

#include <functional>
#include <stdexcept>


template<class Number>
class GeneratorIterator {
protected:
    std::function<Number(std::size_t)> _generator;
    std::size_t _index;
public:
    GeneratorIterator(std::function<Number(std::size_t)> generator, std::size_t start=0);

    GeneratorIterator<Number> operator++();

    GeneratorIterator<Number> operator+(std::size_t shift);

    bool operator==(GeneratorIterator<Number> other);

    Number operator*() const;
};


template<class Number, std::size_t Len>
class Generator {
private:
    std::function<Number(std::size_t)> _generator;

public:
    Generator(std::function<Number(std::size_t)> generator);
    
    GeneratorIterator<Number> begin();

    GeneratorIterator<Number> end();
};


#include "generator.cpp"