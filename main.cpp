#include <iostream>

#include "matrix.hpp"


int main() {
    Matrix<int, 2, 3> m({
        3, 4, 7,
        1, 2, 3
    });

    m[0][1] -= m[1][2];

    Matrix<int, 2, 2> mm({2, 3, 77, 15});

    std::cout << det(mm) << '\n';

    for (auto row: m.rows()) {
        for (auto elem : row)
            std::cout << elem << ' ';
        std::cout << '\n';
    }

    auto t = m.transposed();

    for (auto row : t.rows()) {
        for (auto elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

    Matrix<int, 3, 1> n({
        5,
        8,
        1
    });

    auto res = m * n * 7;
    res += res;

    *res.row(1).begin() = 1;

    for (auto row : res.rows()) {
        for (auto& elem : row) {
            std::cout << elem << ' ';
            elem = 777;
        }
        std::cout << '\n';
    }

    for (auto col : res.columns()) {
        for (auto elem :col) {
            std::cout << elem;
        }
    }
}