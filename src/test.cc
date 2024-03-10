#include <gtest/gtest.h>

#include "matrix.h"

using namespace std;

void SetValueInMatrix(Matrix &matrix, const double *data) {
  int col = matrix.GetCols();
  for (int i = 0; i < matrix.GetRows() * matrix.GetCols(); i++) {
    matrix(i / col, i % col) = data[i];
  }
}

// ************************ Базовый конструктор ************************
TEST(Create, test_1) { Matrix matrix_1; }

// ************************ Конструктор копирования ************************
TEST(Copy, test_1) {
  Matrix matrix_1(3, 3);
  Matrix matrix_2(matrix_1);
  bool result = matrix_1.EqMatrix(matrix_2);
  ASSERT_EQ(result, true);
}

// ******************** Параметризованный конструктор ********************
TEST(ConstructorParametr, test_1) {
  EXPECT_THROW(Matrix matrix_1(-3, 3), invalid_argument);
}

// ************************ Конструктор переноса ************************
TEST(Transfer, test_1) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix matrix(3, 3);
  SetValueInMatrix(matrix, data);
  Matrix matr_result(3, 3);
  SetValueInMatrix(matr_result, data);
  Matrix matrix_res = move(matrix);
  bool result = matrix_res.EqMatrix(matr_result);
  ASSERT_EQ(result, true);
}

// ************** Перегрузка оператора сложения **************
TEST(OverloadPlus, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 3};
  double result[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  Matrix matrix_plus = matrix_1 + matrix_2;
  bool res = matrix_result == matrix_plus;
  ASSERT_EQ(res, false);
}

// ************** Перегрузка оператора вычитания **************
TEST(OverloadSub, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  double result[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 3};
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  Matrix matrix_min = matrix_2 - matrix_1;
  bool res = matrix_result.EqMatrix(matrix_min);
  ASSERT_EQ(res, false);
}

// ************** Перегрузка оператора умножения **************
TEST(OverloadMul, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  double result[] = {315.02, 224.6, 227.88, 213.82, 310.56, 276.98,
                     270.56, 370.96, 948, 733.2, 714.8, 768,
                     289.8, 368.2, 366, 659.8};
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  Matrix matrix_mul = matrix_2 * matrix_1;
  bool res = matrix_result.EqMatrix(matrix_mul);
  ASSERT_EQ(res, true);
}

// ************** Перегрузка оператора умножения для числа **************
TEST(OverloadMulNum, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, data_2);
  Matrix matrix_mul = matrix_1 * 2;
  bool res = matrix_result.EqMatrix(matrix_mul);
  ASSERT_EQ(res, true);
}

// ************************ Перегрузка оператора == ************************
TEST(OverloadEqMatr, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  bool res = matrix_1 == matrix_2;
  ASSERT_EQ(res, false);
}

// ************************ Перегрузка оператора = ************************
TEST(OverloadEqual, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2;
  matrix_2 = matrix_1;
  bool res = matrix_1.EqMatrix(matrix_2);
  ASSERT_EQ(res, true);
}

TEST(OverloadEqual, test_2) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix result(4, 4);
  SetValueInMatrix(result, data);
  Matrix matrix_2;
  matrix_2 = move(matrix_1);
  bool res = matrix_2.EqMatrix(result);
  ASSERT_EQ(res, true);
}

// ************************ Перегрузка оператора += ************************
TEST(OverloadSumEq, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 3};
  double result[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  matrix_1 += matrix_2;
  bool res = matrix_result.EqMatrix(matrix_1);
  ASSERT_EQ(res, false);
}

// ************************ Перегрузка оператора -= ************************
TEST(OverloadSubEq, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  double result[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 3};
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  matrix_2 -= matrix_1;
  bool res = matrix_result.EqMatrix(matrix_2);
  ASSERT_EQ(res, false);
}

// ************************ Перегрузка оператора *= ************************
TEST(OverloadMulEq, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  double result[] = {315.02, 224.6, 227.88, 213.82, 310.56, 276.98,
                     270.56, 370.96, 948, 733.2, 714.8, 768,
                     289.8, 368.2, 366, 659.8};
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  matrix_2 *= matrix_1;
  bool res = matrix_result.EqMatrix(matrix_2);
  ASSERT_EQ(res, true);
}

// ************** Перегрузка оператора *= для числа **************
TEST(OverloadMulEqNum, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, data_2);
  matrix_1 *= 2;
  bool res = matrix_result.EqMatrix(matrix_1);
  ASSERT_EQ(res, true);
}

// ************** Перегрузка оператора индексации **************
TEST(OverloadIndex, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  Matrix const matrix_1(4, 4, data);
  ASSERT_EQ(matrix_1(0, 1), 2);
}

TEST(OverloadIndex, test_2) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  EXPECT_THROW(matrix_1(5, 1), invalid_argument);
}

TEST(OverloadIndex, test_3) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_res[] = {1.1, 777, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                       6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, data_res);
  matrix_1(0, 1) = 777;
  bool result = matrix_1.EqMatrix(matrix_result);
  ASSERT_EQ(result, true);
}

TEST(OverloadIndex, test_4) {
  Matrix matrix_1;
  EXPECT_THROW(matrix_1(5, 1), invalid_argument);
}

TEST(OverloadIndex, test_5) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  EXPECT_THROW(matrix_1(5, 1), invalid_argument);
}

TEST(OverloadIndex, test_6) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  ASSERT_EQ(matrix_1(0, 1), 2);
}

TEST(OverloadIndex, test_7) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  EXPECT_THROW(matrix_1(5, 1), invalid_argument);
}

// ************************ Get ************************
TEST(Getter, test_1) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  int cols = matrix_1.GetCols();
  int rows = matrix_1.GetRows();
  ASSERT_EQ(cols, 4);
  ASSERT_EQ(rows, 4);
}

// ************************ Set ************************
TEST(Setter, test_1) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double data_res[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       11, 12, 13, 14, 15, 16, 0, 0, 0, 0};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(5, 4);
  SetValueInMatrix(matrix_result, data_res);
  matrix_1.SetRows(5);
  bool result = matrix_1.EqMatrix(matrix_result);
  ASSERT_EQ(result, true);
}

TEST(Setter, test_2) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  EXPECT_THROW(matrix_1.SetRows(-1), invalid_argument);
}

TEST(Setter, test_3) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double data_res[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(3, 4);
  SetValueInMatrix(matrix_result, data_res);
  matrix_1.SetRows(3);
  bool result = matrix_1.EqMatrix(matrix_result);
  ASSERT_EQ(result, true);
}

TEST(Setter, test_4) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double data_res[] = {1, 2, 3, 4, 0, 5, 6, 7, 8, 0,
                       9, 10, 11, 12, 0, 13, 14, 15, 16, 0};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(4, 5);
  SetValueInMatrix(matrix_result, data_res);
  matrix_1.SetCols(5);
  bool result = matrix_1 == matrix_result;
  ASSERT_EQ(result, true);
}

TEST(Setter, test_5) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  EXPECT_THROW(matrix_1.SetCols(-1), invalid_argument);
}

TEST(Setter, test_6) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double data_res[] = {1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(4, 3);
  SetValueInMatrix(matrix_result, data_res);
  matrix_1.SetCols(3);
  bool result = matrix_1.EqMatrix(matrix_result);
  ASSERT_EQ(result, true);
}

// ************************ Сравнение матриц ************************
TEST(EqMatrix, test_1) {
  Matrix matrix_1(3, 3);
  Matrix matrix_2(3, 3);
  bool result = matrix_1.EqMatrix(matrix_2);
  ASSERT_EQ(result, true);
}

TEST(EqMatrix, test_2) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data);
  bool result = matrix_1.EqMatrix(matrix_2);
  ASSERT_EQ(result, true);
}

TEST(EqMatrix, test_3) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double data_2[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 3};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  bool result = matrix_1.EqMatrix(matrix_2);
  ASSERT_EQ(result, false);
}

TEST(EqMatrix, test_4) {
  Matrix matrix_1(4, 4);
  Matrix matrix_2(4, 3);
  bool result = matrix_1.EqMatrix(matrix_2);
  ASSERT_EQ(result, false);
}

// ************************ Сложение матриц ************************
TEST(SumMatrix, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                   6, 12, 11, 21, 15, 7, 8, 2};
  double result[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data);
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  matrix_1.SumMatrix(matrix_2);
  ASSERT_EQ(matrix_result.EqMatrix(matrix_1), true);
}

TEST(SumMatrix, test_2) {
  Matrix matrix_1(4, 3);
  Matrix matr_2(4, 4);
  EXPECT_THROW(matrix_1.SumMatrix(matr_2), invalid_argument);
}

TEST(SumMatrix, test_3) {
  Matrix matrix_1;
  Matrix matr_2;
  matr_2.SumMatrix(matrix_1);
  ASSERT_EQ(matr_2.EqMatrix(matrix_1), true);
}

// ************************ Вычитание матриц ************************
TEST(SubMatrix, test_1) {
  double data[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                   12, 24, 22, 42, 30, 14, 16, 4};
  double data_2[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 2};
  double result[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2,
                     6, 12, 11, 21, 15, 7, 8, 2};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  matrix_1.SubMatrix(matrix_2);
  ASSERT_EQ(matrix_result.EqMatrix(matrix_1), true);
}

TEST(SubMatrix, test_2) {
  Matrix matrix_1(4, 3);
  Matrix matr_2(4, 4);
  EXPECT_THROW(matrix_1.SubMatrix(matr_2), invalid_argument);
}

TEST(SubMatrix, test_3) {
  Matrix matrix_1;
  Matrix matr_2;
  matr_2.SumMatrix(matrix_1);
  ASSERT_EQ(matr_2.EqMatrix(matrix_1), true);
}

// ************************ Умножение матрицы на число ************************
TEST(MulNumber, test_1) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double result[] = {2, 4, 6, 8, 10, 12, 14, 16,
                     18, 20, 22, 24, 26, 28, 30, 32};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(4, 4);
  SetValueInMatrix(matrix_result, result);
  matrix_1.MulNumber(2);
  ASSERT_EQ(matrix_result.EqMatrix(matrix_1), true);
}

TEST(MulNumber, test_2) {
  double result[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix matrix_result;
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_1;
  matrix_1.MulNumber(2);
  ASSERT_EQ(matrix_1 == matrix_result, true);
}

// ************************ Перемножение матриц ************************
TEST(MulMatrix, test_1) {
  double data[] = {1.1, 2, 3.4, 8.1, 7.2, 6.3, 4, 5.2, 6};
  double data_2[] = {2.2, 4, 6.8, 16.2, 14.4, 12.6, 8, 10.4,
                     12, 24, 22, 42, 30, 14, 16, 4};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2(4, 4);
  SetValueInMatrix(matrix_2, data_2);
  EXPECT_THROW(matrix_2.MulMatrix(matrix_1), invalid_argument);
}

// ************************ Транспортирование матрицы ************************
TEST(Transpose, test_1) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double result[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(3, 3);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_2 = matrix_1.Transpose();
  ASSERT_EQ(matrix_result.EqMatrix(matrix_2), true);
}

TEST(Transpose, test_2) {
  Matrix matrix_1;
  ASSERT_EQ(matrix_1.Transpose() == matrix_1, true);
}

// ************************ Определитель матрицы ************************
TEST(Determinant, test_1) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  double result = matrix_1.Determinant();
  ASSERT_EQ(result, 0.0);
}

TEST(Determinant, test_2) {
  double data[] = {9.1, 8, 7, 6, 5, 4, 3, 2, 1};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  double result = matrix_1.Determinant();
  ASSERT_DOUBLE_EQ(result, -0.29999999999999716);
}

TEST(Determinant, test_3) {
  double data[] = {1, 0, 0, 0, 0, 4, 0, 0, 0};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  double result = matrix_1.Determinant();
  ASSERT_DOUBLE_EQ(result, 0.0);
}

TEST(Determinant, test_4) {
  double data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  double result = matrix_1.Determinant();
  ASSERT_DOUBLE_EQ(result, 0.0);
}

TEST(Determinant, test_5) {
  double data[] = {51, 2, 2, 1, 0, 0, 3, 43, 0, 0, 0, 3, 51, 0, 0, 1};
  Matrix matrix_1(4, 4);
  SetValueInMatrix(matrix_1, data);
  double result = matrix_1.Determinant();
  ASSERT_DOUBLE_EQ(result, -918.0);
}

TEST(Determinant, test_6) {
  double data[] = {51, 2, 2, 1, 0, 0, 3, 43, 0, 0, 0, 3};
  Matrix matrix_1(3, 4);
  SetValueInMatrix(matrix_1, data);
  EXPECT_THROW(matrix_1.Determinant(), invalid_argument);
}

// ************************ CalcComplements матрицы ************************
TEST(CalcComplements, test_1) {
  double data[] = {6.7, 5, -4, 99};
  double result[] = {99, 4, -5, 6.7};
  Matrix matrix_1(2, 2);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(2, 2);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_2 = matrix_1.CalcComplements();
  ASSERT_EQ(matrix_2.EqMatrix(matrix_result), true);
}

TEST(CalcComplements, test_2) {
  double data[] = {2, 0, 0, 0, 2, 0, 0, 0, 2};
  double result[] = {4, 0, 0, 0, 4, 0, 0, 0, 4};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(3, 3);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_2 = matrix_1.CalcComplements();
  ASSERT_EQ(matrix_2.EqMatrix(matrix_result), true);
}

TEST(CalcComplements, test_3) {
  double data[] = {2, 0, 0, 0, 2, 0};
  double result[] = {4, 0, 0, 0, 4, 0, 0, 0, 4};
  Matrix matrix_1(2, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(3, 3);
  SetValueInMatrix(matrix_result, result);
  EXPECT_THROW(matrix_1.CalcComplements(), invalid_argument);
}

TEST(CalcComplements, test_4) {
  double data[] = {1, 2, 3, 4};
  double result[] = {4, -3, -2, 1};
  Matrix matrix_1(2, 2);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(2, 2);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_2 = matrix_1.CalcComplements();
  ASSERT_EQ(matrix_2.EqMatrix(matrix_result), true);
}

TEST(CalcComplements, test_5) {
  double data[] = {1};
  double result[] = {1};
  Matrix matrix_1(1, 1);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(1, 1);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_2 = matrix_1.CalcComplements();
  bool res = matrix_2.EqMatrix(matrix_result);
  ASSERT_EQ(res, true);
}

// ************************ InverseMatrix ************************
TEST(InverseMtrix, test_1) {
  double data[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double result[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_result(3, 3);
  SetValueInMatrix(matrix_result, result);
  Matrix matrix_2 = matrix_1.InverseMatrix();
  ASSERT_EQ(matrix_2.EqMatrix(matrix_result), true);
}

TEST(InverseMtrix, test_2) {
  double data[] = {2, 5, 7, 6, 3, 4};
  double result[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  Matrix matrix_1(2, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2;
  Matrix matrix_result(3, 3);
  SetValueInMatrix(matrix_result, result);
  EXPECT_THROW(matrix_2 = matrix_1.InverseMatrix(), invalid_argument);
}

TEST(InverseMtrix, test_3) {
  double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double result[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix matrix_1(3, 3);
  SetValueInMatrix(matrix_1, data);
  Matrix matrix_2;
  Matrix matrix_result(3, 3);
  SetValueInMatrix(matrix_result, result);
  EXPECT_THROW(matrix_2 = matrix_1.InverseMatrix(), invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}