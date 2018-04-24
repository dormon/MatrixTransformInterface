#pragma once

#include <array>

#include <MatrixTransformInterface/NodeAttribute.h>

namespace matrixTransform {

/**
 * @brief Transformation matrix 4x4
 * Order of elements:
 * |0 4 8 C|
 * |1 5 9 D|
 * |2 6 A E|
 * |3 7 B F|
 */
using Matrix = std::array<float, 16>;

class MatrixNodeAttribute : public NodeAttribute {
  public:
  MatrixNodeAttribute(Matrix const& m) : NodeAttribute(MATRIX), data(m) {}
  Matrix getMatrix() const { return data; }
  void   setMatrix(Matrix const& m) { data = m; }

  protected:
  Matrix data;
};

}  // namespace matrixTransform
