#include <iostream>

#include "matrix/matrix.hpp"

int main() {
    Matrix<int, 2, 3> m({
        3, 4, 7,
        1, 2, 3
    });

    Matrix<int, 3, 1> n({
        5,
        8,
        1
    });

    auto res = m * n;
    for (auto row : res.rows()) {
        for (auto elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}