#pragma once

#include<MatrixTransformInterface/Fwd.h>
#include<MatrixTransformInterface/AABB.h>

namespace matrixTransform {

/**
 * @brief Custom node attribute
 */
class NodeAttribute {
  public:
};

using NodeAttributePointer = std::shared_ptr<NodeAttribute>;
using NodeAttributes       = std::vector<NodeAttributePointer>;
using UserID               = uint32_t;
using UserIDs              = std::vector<UserID>;

class FrustumCullingNodeAttribute : public NodeAttribute {
  public:
  AABB aabb;  ///< axis aligned bounding box
};

class UserIDsNodeAttribute : public NodeAttribute {
  public:
  UserIDs userIds = {};
};

};  // namespace matrixTransform
