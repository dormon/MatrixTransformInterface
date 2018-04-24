#pragma once

#include <MatrixTransformInterface/APIAbstraction.h>
#include <MatrixTransformInterface/OutputAttribute.h>
#include <memory>

namespace matrixTransform {

class UserIDsOutputAttribute : public OutputAttribute {
  public:
  std::shared_ptr<Buffer>
                          offsets;  ///< which matrices are associated with which userId
  std::shared_ptr<Buffer> userIds;  ///< unique userIds of nodes
  std::shared_ptr<Buffer>
      nofIds;  ///< number of unique userIds - single uint32_t
};

}  // namespace matrixTransform
