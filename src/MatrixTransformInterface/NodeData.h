#pragma once

#include <MatrixTransformInterface/NodeAttribute.h>

namespace matrixTransform {

using NodeAttributePointer = std::unique_ptr<NodeAttribute>;
using NodeAttributes       = std::vector<NodeAttributePointer>;

/**
 * @brief Node Data
 * A node is composed of node attributes (such as Matrix, OUTPUT flag, AABB,
 * ...)
 */
class NodeData {
  public:
  NodeAttributes attributes = {};  ///< node attributes
};

}  // namespace matrixTransform
