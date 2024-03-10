#include "matrix.h"

//CONSTRUCTORS

Matrix::Matrix() : rows_(1), cols_(1) {
  CreateMatrixCurrent();
}

Matrix::Matrix(int val_row, int val_col) {
  ValidInputSize(val_row, val_col);
  rows_ = val_row;
  cols_ = val_col;
  CreateMatrixCurrent();
}

Matrix::Matrix(int val_row, int val_col, const double *data) {
  ValidInputSize(val_row, val_col);
  rows_ = val_row;
  cols_ = val_col;
  CreateMatrixCurrent();
  FillingMatrix(data);
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrixCurrent();
  CopyMatrix(other);
}

Matrix::Matrix(Matrix &&other) noexcept : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() { FreeMatrixCurrent(); }

bool Matrix::EqMatrix(const Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < cols_; ++y) {
      if (fabs(matrix_[i][y] - other.matrix_[i][y]) > EPS_) {
        return false;
      }
    }
  }
  return true;
}

// BASIC METHODS

void Matrix::SumMatrix(const Matrix &other) {
  ValidSameSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < cols_; ++y) {
      matrix_[i][y] = matrix_[i][y] + other.matrix_[i][y];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  ValidSameSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < cols_; ++y) {
      this->matrix_[i][y] = matrix_[i][y] - other.matrix_[i][y];
    }
  }
}

void Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < cols_; ++y) {
      matrix_[i][y] = matrix_[i][y] * num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error: the number of columns of the first matrices must be equal to "
        "the number of rows of the second matrices");
  }
  auto **temp = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    temp[i] = new double[other.cols_]{};
  }
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < other.cols_; ++y) {
      for (int k = 0; k < cols_; ++k) {
        temp[i][y] += matrix_[i][k] * other.matrix_[k][y];
      }
    }
  }
  FreeMatrixCurrent();
  matrix_ = temp;
  cols_ = other.cols_;
  temp = nullptr;
}

Matrix Matrix::Transpose() const {
  Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int y = 0; y < result.cols_; ++y) {
      result.matrix_[i][y] = matrix_[y][i];
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  ValidValSize(rows_, cols_);
  Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    Matrix temp(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; ++i) {
      for (int y = 0; y < cols_; ++y) {
        this->MatrixReduction(temp, i, y);
        result.matrix_[i][y] = pow(-1.0, (double) (i + y)) * temp.Determinant();
      }
    }
  }
  return result;
}

double Matrix::Determinant() {
  ValidSquare();
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (rows_ == 3) {
    return DeterminantThirdOrder();
  } else {
    return ComplexDeterminant();
  }
}

Matrix Matrix::InverseMatrix() {
  ValidSquare();
  double det = Determinant();
  if (fabs(det - 0) <= EPS_) {
    throw std::invalid_argument("the inverse matrix does not exist because the determinant of the current one is 0");
  }
  Matrix result = CalcComplements().Transpose();
  result.MulNumber(1 / det);
  return result;
}

// SECONDARY METHODS

double Matrix::DeterminantThirdOrder() {
  double res = matrix_[0][0] * matrix_[1][1] * matrix_[2][2] + matrix_[0][1] * matrix_[1][2] * matrix_[2][0]
      + matrix_[0][2] * matrix_[1][0] * matrix_[2][1] - matrix_[0][2] * matrix_[1][1] * matrix_[2][0]
      - matrix_[0][1] * matrix_[1][0] * matrix_[2][2] - matrix_[0][0] * matrix_[1][2] * matrix_[2][1];
  return res;
}

double Matrix::ComplexDeterminant() const {
  double det = 1.0;
  Matrix temp_matrix(*this);
  for (int i = 0; i < temp_matrix.rows_; ++i) {
    if (temp_matrix.NullRowCol()) {
      return 0.0;
    }
    if (fabs(temp_matrix.matrix_[i][i] - 0) <= EPS_) {
      for (int j = 1 + 1; j < temp_matrix.rows_; ++j) {
        if (fabs(temp_matrix.matrix_[j][i] - 0) > EPS_) {
          for (int k = 0; k < temp_matrix.cols_; ++k) {
            temp_matrix.matrix_[i][k] += temp_matrix.matrix_[j][k];
          }
          break;
        }
      }
    }
    if (fabs(temp_matrix.matrix_[i][i] - 0) > EPS_) {
      for (int j = i + 1; j < temp_matrix.rows_; ++j) {
        double temp = temp_matrix.matrix_[j][i] / temp_matrix.matrix_[i][i] * -1;
        for (int y = 0; y < temp_matrix.cols_; ++y) {
          temp_matrix.matrix_[j][y] += temp_matrix.matrix_[i][y] * temp;
        }
      }
    }
  }
  for (int i = 0; i < temp_matrix.rows_; ++i) {
    det *= temp_matrix(i, i);
  }
  return det;
}

bool Matrix::NullRowCol() const {
  for (int i = 0; i < rows_; ++i) {
    int err = 0;
    for (int y = 0; y < cols_; ++y) {
      if (fabs(matrix_[i][y] - 0) > EPS_) {
        err = 1;
        break;
      }
    }
    if (!err) {
      return true;
    }
  }
  for (int i = 0; i < cols_; ++i) {
    int err = 0;
    for (int y = 0; y < rows_; ++y) {
      if (fabs(matrix_[y][i] - 0) > EPS_) {
        err = 1;
        break;
      }
    }
    if (!err) {
      return true;
    }
  }
  return false;
}

void Matrix::MatrixReduction(Matrix &temp, int row, int col) const {

  int x = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row) {
      int y = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != col) {
          temp.matrix_[x][y] = matrix_[i][j];
          y++;
        }
      }
      x++;
    }
  }
}

void Matrix::CreateMatrixCurrent() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

void Matrix::FillingMatrix(const double *data) {
  int index = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < cols_; ++y) {
      matrix_[i][y] = data[index];
      ++index;
    }
  }
}

double **Matrix::CopyMatrix(const Matrix &other) {
  for (int i = 0; i < rows_; ++i) {
    for (int y = 0; y < cols_; ++y) {
      matrix_[i][y] = other.matrix_[i][y];
    }
  }
  return matrix_;
}

void Matrix::CopyMatrixVarRow(int row, double **matrix) {
  if (row > rows_) {
    for (int i = 0; i < rows_; ++i) {
      for (int y = 0; y < cols_; ++y) {
        matrix[i][y] = matrix_[i][y];
      }
    }
  } else if (row < rows_) {
    for (int i = 0; i < row; ++i) {
      for (int y = 0; y < cols_; ++y) {
        matrix[i][y] = matrix_[i][y];
      }
    }
  }
}

void Matrix::CopyMatrixVarCol(int col, double **matrix) {
  if (col > cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int y = 0; y < cols_; ++y) {
        matrix[i][y] = matrix_[i][y];
      }
    }
  } else if (col < rows_) {
    for (int i = 0; i < rows_; ++i) {
      for (int y = 0; y < col; ++y) {
        matrix[i][y] = matrix_[i][y];
      }
    }
  }
}

void Matrix::FreeMatrixCurrent() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i]) {
        delete[] matrix_[i];
        matrix_[i] = nullptr;
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void Matrix::ValidValSize(int row, int col) const {
  if (row < 0 || col < 0) {
    throw std::invalid_argument("Error: the number of rows and cols must be greater or equal than 0");
  }
  if (row > rows_ || col > cols_) {
    throw std::invalid_argument("row and column index must not be greater than the size of the matrix");
  }
}

void Matrix::ValidInputSize(int row, int col) const {
  if (row < 1 || col < 1) {
    throw std::invalid_argument(
        "Error: the number of rows and cols must be greater or equal than 0");
  }
}

void Matrix::ValidSquare() const {
  if (rows_ != cols_) { throw std::invalid_argument("the number of rows must be equal to the number of columns"); }
}

void Matrix::ValidSameSize(const Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Error: matrices must have the same size");
  }
}

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(int const &row) {
  if (row < 1) {
    throw std::invalid_argument(
        "Error: the number of rows must be greater than 1");
  }
  auto **temp = new double *[row];
  for (int i = 0; i < row; ++i) {
    temp[i] = new double[cols_]{};
  }
  CopyMatrixVarRow(row, temp);
  FreeMatrixCurrent();
  rows_ = row;
  matrix_ = temp;
}

void Matrix::SetCols(int const &col) {
  if (col < 1) {
    throw std::invalid_argument(
        "Error: the number of cols must be greater than 1");
  }
  auto **temp = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    temp[i] = new double[col]{};
  }
  CopyMatrixVarCol(col, temp);
  FreeMatrixCurrent();
  cols_ = col;
  matrix_ = temp;
}

// OVERLOADING OF OPERATORS

Matrix Matrix::operator+(const Matrix &other) const {
  Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

void Matrix::operator+=(const Matrix &other) { SumMatrix(other); }

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

void Matrix::operator-=(const Matrix &other) { SubMatrix(other); }

Matrix Matrix::operator*(const double &num) const {
  Matrix res(*this);
  res.MulNumber(num);
  return res;
}

void Matrix::operator*=(const double &num) { MulNumber(num); }

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

void Matrix::operator*=(const Matrix &other) { MulMatrix(other); }

bool Matrix::operator==(const Matrix &other) const { return EqMatrix(other); }

Matrix &Matrix::operator=(const Matrix &other) {
  FreeMatrixCurrent();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrixCurrent();
  matrix_ = CopyMatrix(other);

  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    FreeMatrixCurrent();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
  }
  return *this;
}

double Matrix::operator()(int row, int col) const {
  ValidValSize(row, col);
  return matrix_[row][col];
}

double &Matrix::operator()(int row, int col) {
  ValidValSize(row, col);
  return matrix_[row][col];
}
