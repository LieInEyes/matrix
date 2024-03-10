#include "matrix.h"

void SetValueInMatrix(Matrix &matrix, const double *data) {
  int col = matrix.GetCols();
  for (int i = 0; i < matrix.GetRows() * matrix.GetCols(); i++) {
    matrix(i / col, i % col) = data[i];
  }
}

int main() {

  double data[] = {0, 2, 3, 0, 5, 6, 0, 8, 9};
  Matrix matrix(3, 3);
  SetValueInMatrix(matrix, data);

  return 0;
}
