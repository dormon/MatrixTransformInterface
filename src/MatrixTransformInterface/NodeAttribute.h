#pragma once

#include<MatrixTransformInterface/Fwd.h>
#include<MatrixTransformInterface/AABB.h>

namespace matrixTransform {

/**
 * @brief Custom node attribute
 */
class NodeAttribute {
  public:
    enum Type{
      MATRIX ,
      OUTPUT ,
      USER_ID,
      AABB   ,
    };
    NodeAttribute(Type const&t):type(t){}
    virtual ~NodeAttribute(){};
    Type getType()const{return type;}
  protected:
    Type type;
};

/*
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
*/

};  // namespace matrixTransform
