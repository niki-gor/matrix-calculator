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

TEST(TestMatrix, TestDiagonalRowColumn) { // извлечение диагонали, строки, столбца
    Matrix<int, 2, 3> m({
    1, 2, 3,
    4, 5, 6
    });
    auto diag = m.main_diagonal().copy();
    EXPECT_EQ(diag, (Slice<int, 2>({1, 5})));
    diag[1] = 777;
    EXPECT_EQ(diag, (Slice<int, 2>({1, 777})));
    EXPECT_EQ(m, (Matrix<int, 2, 3>({  // исходная матрица не изменилась
        1, 2, 3, 
        4, 5, 6})));

    auto row = m.row(1).copy();
    EXPECT_EQ(row, (Slice<int, 3>({4, 5, 6})));
    row[0] = 777;
    EXPECT_EQ(m, (Matrix<int, 2, 3>({
        1, 2, 3, 
        4, 5, 6})));

    auto col = m.column(0).copy();
    EXPECT_EQ(col, (Slice<int, 2>({1, 4})));
    col[1] = 777;
    EXPECT_EQ(m, (Matrix<int, 2, 3>({
        1, 2, 3, 
        4, 5, 6})));
}

TEST(TestMatrix, TestConstructors) { // составление векторов из чисел, матрицы из векторов, матрицы из чисел
    Slice<int, 3> row1({1, 2, 3});
    Slice<int, 3> row2({4, 5, 6});
    Matrix<int, 2, 3> m({row1, row2});
    EXPECT_EQ(m, (Matrix<int, 2, 3>({
        1, 2, 3, 
        4, 5, 6})));
}

TEST(TestMatrix, TestAddSub) { // сложение/вычитание/умножение объектов одинаковой размерности
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

    Slice<int, 2> v1 = Slice<int, 2>({1, 2});
    Slice<int, 2> v2 = Slice<int, 2>({10, 15});
    EXPECT_EQ(v1 + v2, (Slice<int, 2>({11, 17})));
    EXPECT_EQ(v1 - v2, (Slice<int, 2>({-9, -13})));
    EXPECT_EQ(v1 * v2, 40); // скалярное произведение
}

TEST(TestMatrix, TestSlicesAreSlices) { // проверка работоспособности слайсов
    Matrix<int, 2, 3> m({
    1, 2, 3,
    4, 5, 6
    });
    auto diag = m.main_diagonal();
    diag[1] = 777;
    EXPECT_EQ(m, (Matrix<int, 2, 3>({
        1, 2, 3, 
        4, 777, 6})));
    
    auto row = m[0];
    row[0] = 1337;
    EXPECT_EQ(m, (Matrix<int, 2, 3>({
        1337, 2, 3, 
        4, 777, 6})));
    
    m.column(2)[0] = 111111;
    EXPECT_EQ(m, (Matrix<int, 2, 3>({
        1337, 2, 111111, 
        4, 777, 6})));
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
