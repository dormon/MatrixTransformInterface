#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace matrixTransform {

/**
 * @brief unique node identifier
 */
using NodeID = std::size_t;

/**
 * @brief Childred and parents are stored in ordered lists
 * NodeIndex is index to these lists
 */
using NodeIndex = size_t;


using Vec3 = std::array<float, 3>;

class NodeAttribute;
class FrustumCullingNodeAttribute;
class UserIDsNodeAttribute;

class NodeData;
class Buffer;
class OutputAttribute;
class UserIDsOutputAttribute;

using NodeAttributePointer   = std::unique_ptr<NodeAttribute>;
using NodeAttributes         = std::vector<NodeAttributePointer>;
using OutputAttributePointer = std::unique_ptr<OutputAttribute>;
using OutputAttributes       = std::vector<OutputAttributePointer>;

using BufferPointer = std::shared_ptr<Buffer>;

}  // namespace matrixTransform
