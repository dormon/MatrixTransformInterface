#pragma once

#include<MatrixTransformInterface/Fwd.h>

namespace matrixTransform{

/**
 * @brief Axis aligned bounding box
 */
struct AABB {
  Vec3 corner = {{0.f, 0.f, 0.f}};  ///< coordinates of smallest AABB corner
  Vec3 size   = {{1.f, 1.f, 1.f}};  ///< size of bounding box
};

}
