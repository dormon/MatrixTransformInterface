/**
 * @file This file contains abstraction over rendering/GPGPU APIs (such as
 * OpenGL/OpenCL/Cuda/DirectX)
 *
 * @author Tomáš Milet
 */

#pragma once

namespace matrixTransform {

/**
 * @brief This class represents interface for GPU buffers.
 * The main purpose of this class is to abstract GPGPU buffers such as
 * (cl::Buffer, glCreateBuffer(buffer), ... )
 */
class Buffer {
  public:
  virtual ~Buffer() {}
};

}  // namespace matrixTransform
