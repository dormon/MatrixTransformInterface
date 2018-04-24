#pragma once

#include <map>
#include <memory>

#include <MatrixTransformInterface/OutputAttribute.h>

namespace matrixTransform {

using OutputAttributePointer = std::shared_ptr<OutputAttribute>;

class OutputData {
  public:
  OutputAttributePointer getAttribute(OutputAttribute::Type const& type) const {
    return attributes.at(type);
  }

  protected:
  std::map<OutputAttribute::Type, OutputAttributePointer> attributes;
};

}  // namespace matrixTransform
