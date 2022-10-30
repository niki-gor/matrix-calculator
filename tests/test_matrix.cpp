#include <gtest/gtest.h>

#include "matrix.hpp"


double EPS = 1e-9;


TEST(TestMatrix, TestIndices) { // обращение по индексу
    Matrix<int, 2, 3> m({
    1, 2, 3, 
    4, 5, 6});
    EXPECT_EQ(m[1][2], 6);
    EXPECT_EQ(m[0][1], 2);
}

TEST(TestMatrix, TestAddSub) { // сложение/вычитание матриц
    Matrix<int, 2, 3> m({
    1, 2, 3, 
    4, 5, 6});
    Matrix<int, 2, 3> n({
    0, 0, -3,
    4, 0, 1000000
    });

    auto add = m + n;
    Matrix<int, 2, 3> add_res({
        1, 2, 0,
        8, 5, 1000006
    });
    EXPECT_EQ(add, add_res);

    auto sub = m - n;
    Matrix<int, 2, 3> sub_res({
        1, 2, 6,
        0, 5, -999994
    });
    EXPECT_EQ(sub, sub_res);
}

TEST(TestMatrix, TestDet) {
    Matrix<int, 2, 2> m({
        0, 0,
        1, 1
    });
    EXPECT_EQ(det(m), 0);

    Matrix<int, 3, 3> m2({
        34, 11, 6,
        -234, 1, 76,
        778, 15, -3
    });
    EXPECT_NEAR(det(m2), 578096, EPS);
}