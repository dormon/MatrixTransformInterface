/**
 * @file
 * @brief This file contains matrix transform interface.
 * OpenCL/DirectX/OpenGL specific classes should implement this interface.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <set>
#include <vector>

#include <MatrixTransformInterface/ComputeParameter.h>
#include <MatrixTransformInterface/Fwd.h>
#include <MatrixTransformInterface/NodeAttribute.h>

namespace matrixTransform {

/**
 * @brief unique node identifier
 */
using NodeID = std::size_t;

/**
 * @brief Childred and parents are stored in ordered lists
 * NodeIndex is index to these lists
 */
using NodeIndex = std::size_t;

/**
 * @brief This class represents interface of GPU based scene graph with
 * transformations. Classes that implement this interface will have custom
 * constructors. These constructors should provide OpenCL context and Device or
 * OpenGL context, or ...
 *
 * All commands (such as createNode, insertToChildren, ...) are stored in
 * command list. This command list is then uploaded to GPU as single transaction
 * in order to reduce CPU <-> GPU communication overhead.
 */
class GPUTransform {
  public:
  enum Feature {
    USE_FRUSTUM_CULLING,  ///< activate frustum culling
    /**
     * @brief Each node can contain list of user ids (uint32_t) identifying user
     * data (meshes, ...)
     */
    USE_USER_IDS,
    // TO BE EXTENDED
  };
  /**
   * @brief Set of features
   */
  using Features = std::set<Feature>;
  /**
   * @brief Constructor 
   *
   * @param features feature set
   */
  GPUTransform(Features const& features = {});
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
   * @brief This function sets global scene parameters needed by computation.
   * One of the compute parameter will be view matrix for frustum culling.
   *
   * @param type type of compute parameter
   * @param data compute parameter data
   */
  virtual void setComputeParameter(
      ComputeParameter::Type const&            type,
      std::shared_ptr<ComputeParameter> const& data);
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
   * @brief The master root node is virtual node.
   * The master root node does not contain any data.
   * It exists only for convinience.
   * If your application requires multiple roots, all of them must be children
   * of the master root node. Children of the master root node are traversed
   * during computation.
   */
  NodeID static const masterRootNode = 0;
};

}  // namespace matrixTransform
