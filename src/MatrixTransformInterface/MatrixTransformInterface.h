#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include <MatrixTransformInterface/Fwd.h>
#include <MatrixTransformInterface/NodeAttribute.h>

namespace matrixTransform {

/**
 * @brief Node Data
 * Node data has to contain transformation matrix and isOutput flag.
 * Node can also contain additional attributes (frustum culling aabb, user ids,
 * ...)
 */
class NodeData {
  public:
  Matrix         data;                ///< transformation matrix
  bool           isOutput   = false;  ///< is output of this node needed?
  NodeAttributes attributes = {};     ///< additional node attributes
};

class Buffer {
  public:
  virtual ~Buffer() {}
};

class OutputAttribute {};

class UserIDsOutputAttribute : public OutputAttribute {
  public:
  BufferPointer offsets;  ///< which matrices are associated with which userId
  BufferPointer userIds;  ///< unique userIds of nodes that passed the condition
  BufferPointer nofIds;   ///< number of unique userIds
};

class Output {
  public:
  std::shared_ptr<Buffer> matrices;
  OutputAttributes        attributes;
};

/**
 * @brief This class represents interface of GPU based scene graph with
 * transformations Classes that implement this interface will have custom
 * constructors. These constructors should provide OpenCL context and Device or
 * OpenGL context, or ...
 *
 * All commands (such as createNode, insertToChildren, ...) are stored in
 * command list. This command list is then uploaded to GPU as single transaction
 * in order to reduce CPU <-> GPU communication overhead.
 */
class GPUTransform {
  public:
  /**
   * @brief Destructor
   */
  virtual ~GPUTransform() {}
  /**
   * @brief This function will create free node.
   *
   * @param data node data
   *
   * @return id of node
   */
  virtual NodeID createNode(NodeData const& data) = 0;
  /**
   * @brief This function will delete node from graph
   * If the node is connected to other nodes, all those connections will be
   * disconnected
   *
   * @param node id of node
   */
  virtual void deleteNode(NodeID const& node) = 0;
  /**
   * @brief This function returns number of children of target node
   *
   * @param target id of parent node
   *
   * @return number of children
   */
  virtual NodeIndex getNofChildren(
      NodeID const& target = masterRootNode) const = 0;
  /**
   * @brief This function returns child of target node
   *
   * @param childIndex index of child (childred are stored in ordered list)
   * @param target id of parent node
   *
   * @return id of child node
   */
  virtual NodeID getChild(NodeIndex const& childIndex,
                          NodeID const&    target = masterRootNode) const = 0;
  /**
   * @brief This function returns number of parents of target node
   *
   * @param target id of child node
   *
   * @return number of parents
   */
  virtual NodeIndex getNofParents(NodeID const& target) const = 0;
  /**
   * @brief This function returns parent id of target node
   *
   * @param parentIndex index of parent (parent are stored in ordered list)
   * @param target id of child node
   *
   * @return id of parent node
   */
  virtual NodeID getParent(NodeIndex const& parentIndex,
                           NodeID const&    target) const = 0;
  /**
   * @brief This function inserts child to the end of the ordered child list of
   * the target node
   *
   * @param newChild id of child that will be inserted
   * @param target id of parent node
   */
  virtual void appedToChildren(NodeID const& newChild,
                               NodeID const& target = masterRootNode) = 0;
  /**
   * @brief This function inserts child to the beginning of the ordered child
   * list of the target node
   *
   * @param newChild id of child that will be inserted
   * @param target id of parent node
   */
  virtual void prependToChildren(NodeID const& newChild,
                                 NodeID const& target = masterRootNode) = 0;
  /**
   * @brief This function remove child from ordered child list of the target
   * node. All following children will be shifted toward the beginning of the
   * ordered list. This function will note delete node it only disconnects these
   * to nodes.
   *
   * @param childIndex Index of child that will be removed
   * @param target id of parent node
   */
  virtual void removeFromChildren(NodeIndex const& childIndex,
                                  NodeID const&    target = masterRootNode) = 0;
  /**
   * @brief This function inserts child to the ordered child list of the target
   * node
   *
   * @param childIndex index of element to which the child will be inserted
   * @param newChild id of child
   * @param target id of parent node
   */
  virtual void insertToChildred(NodeIndex const& childIndex,
                                NodeID const&    newChild,
                                NodeID const&    target = masterRootNode) = 0;

  /**
   * @brief This function updates node data
   *
   * @param node id of node
   * @param data new data
   */
  virtual void updateNodeData(NodeID node, NodeData const& data) = 0;
  /**
   * @brief This function returns node's data
   *
   * @param node id of node
   *
   * @return node's data
   */
  virtual NodeData const& getNodeData(NodeID node) const = 0;

  /**
   * @brief This function uploads all changes to GPU.
   *
   * @param blocking if blocking == true this command will not return until all
   * computation is done. if blocksing == false this command will return
   * immidiately
   */
  virtual void compute(bool blocking = false) = 0;
  /**
   * @brief This function return true if all changes are computed on GPU.
   *
   * @return true if all changes are computed
   */
  virtual bool isFinished() const = 0;  // future?
  /**
   * @brief This function waits for all changes to be computed.
   * This function is blocking.
   */
  virtual void finish() = 0;

  /**
   * @brief Root node is virtual and in fact does not exists.
   * Root node does not contain any data.
   * It exists only for convinience.
   * If your application requires multiple roots, all of them must be children
   * of root node. Children of the root node are traversed during computation.
   * The root node does not have
   */
  NodeID static const masterRootNode = 0;
};

}  // namespace matrixTransform
