/**
 * @file
 * @brief This file contain CPU representation of axis aligned bounding box.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#pragma once

#include <MatrixTransformInterface/Fwd.h>

namespace matrixTransform {

using Vec3 = std::array<float,3>;

/**
 * @brief Axis aligned bounding box
 */
struct AABB {
  Vec3 corner = {{0.f, 0.f, 0.f}};  ///< coordinates of smallest AABB corner
  Vec3 size   = {{1.f, 1.f, 1.f}};  ///< size of bounding box
};

}  // namespace matrixTransform
