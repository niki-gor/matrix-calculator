#include <iostream>

#include "matrix/matrix.hpp"

int main() {
    Matrix<int, 2, 3> m({
        3, 4, 7,
        1, 2, 3
    });

    auto c = m.row(1).copy();
    for (auto& i : c) {
        std::cout << i << ' ';
    }

    m = -m;

    for (auto row : m.rows()) {
        for (auto elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}