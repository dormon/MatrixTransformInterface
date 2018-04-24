#pragma once

namespace matrixTransform {

class OutputAttribute {
  public:
  enum Type {
    MATRICES,
    USER_IDS,
  };
  OutputAttribute(Type const& t) : type(t) {}
  virtual ~OutputAttribute() {}
  Type getType() const { return type; }

  protected:
  Type type;
};

}  // namespace matrixTransform
