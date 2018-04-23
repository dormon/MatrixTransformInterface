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

/**
 * @brief Transformation matrix 4x4
 * Order of elements:
 * |0 4 8 C|
 * |1 5 9 D|
 * |2 6 A E|
 * |3 7 B F|
 */
using Matrix = std::array<float, 16>;

using Vec3 = std::array<float, 3>;

class NodeAttribute;
class FrustumCullingNodeAttribute;
class UserIDsNodeAttribute;

class NodeData;
class Buffer;
class OutputAttribute;
class UserIDsOutputAttribute;

using OutputAttributePointer = std::shared_ptr<OutputAttribute>;
using OutputAttributes       = std::vector<OutputAttributePointer>;

using BufferPointer = std::shared_ptr<Buffer>;

}  // namespace matrixTransform
