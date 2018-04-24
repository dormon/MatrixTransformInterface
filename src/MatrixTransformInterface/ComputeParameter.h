#pragma once

namespace matrixTransform {

class ComputeParameter {
  public:
  enum Type {
    CPU_CAMERA,
    GPU_CAMERA,
    //TO BE EXTENDED
  };
  virtual ~ComputeParameter(){}
  ComputeParameter() = delete;
};

}  // namespace matrixTransform
