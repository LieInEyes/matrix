#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cmath>
#include <iostream>

class Matrix {
 public:
  Matrix();

  Matrix(int val_row, int val_col);

  Matrix(int val_row, int val_col, const double *data);

  Matrix(const Matrix &other);

  Matrix(Matrix &&other) noexcept;

  ~Matrix();

  bool EqMatrix(const Matrix &other) const;

  void SumMatrix(const Matrix &other);

  void SubMatrix(const Matrix &other);

  void MulNumber(double num);

  void MulMatrix(const Matrix &other);

  Matrix Transpose() const;

  Matrix CalcComplements();

  double Determinant();

  Matrix InverseMatrix();

  int GetRows() const;

  int GetCols() const;

  void SetRows(int const &row);

  void SetCols(int const &col);

  Matrix operator+(const Matrix &other) const;

  void operator+=(const Matrix &other);

  Matrix operator-(const Matrix &other) const;

  void operator-=(const Matrix &other);

  Matrix operator*(const double &num) const;

  void operator*=(const double &num);

  Matrix operator*(const Matrix &other) const;

  void operator*=(const Matrix &other);

  bool operator==(const Matrix &other) const;

  Matrix &operator=(const Matrix &other);

  Matrix &operator=(Matrix &&other) noexcept;

  double operator()(int row, int col) const;

  double &operator()(int row, int col);

 private:
  int rows_;

  int cols_;

  double **matrix_;

  const double EPS_ = 0.000001;

  double DeterminantThirdOrder();

  bool NullRowCol() const;

  double ComplexDeterminant() const;

  void MatrixReduction(Matrix &temp, int row, int col) const;

  void CreateMatrixCurrent();

  void FillingMatrix(const double *data);

  double **CopyMatrix(const Matrix &other);

  void CopyMatrixVarRow(int row, double **matrix);

  void CopyMatrixVarCol(int col, double **matrix);

  void FreeMatrixCurrent();

  void ValidValSize(int row, int col) const;

  void ValidInputSize(int row, int col) const;

  void ValidSquare() const;

  void ValidSameSize(const Matrix &other) const;
};

#endif// SRC_MATRIX_H_