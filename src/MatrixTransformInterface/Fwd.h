/**
 * @file
 * @brief This file contains forward declarations.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */
#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace matrixTransform {

class NodeData;

class NodeAttribute;
class FrustumCullingNodeAttribute;
class UserIDsNodeAttribute;

class OutputAttribute;
class MatricesOutputAttribute;
class UserIDsOutputAttribute;

class ComputeParameter;
class CPUCamera;
class GPUCamera;

class Buffer;

class GPUTransform;

}  // namespace matrixTransform
