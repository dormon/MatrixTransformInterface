#pragma once

namespace matrixTransform {

/**
 * @brief This class represents parameter for scene graph traversal.
 * A scene graph traversal could require different parameters (such as view camera matrix).
 */
class ComputeParameter {
  public:
  enum Type {
    CPU_CAMERA,/// < camera is stored on CPU
    GPU_CAMERA,/// < camera is stored on GPU in Buffer (matrix 4x4, floats, column-major)
    // TO BE EXTENDED
  };
  /**
   * @brief Destructor
   */
  virtual ~ComputeParameter() {}
  ComputeParameter() = delete;
};

}  // namespace matrixTransform
