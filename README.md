# MatrixTransformInterface
Interface for matrix transformation computed on GPU

/**
 * @brief Output of GPUTransform computation.
 * Matrices contains all node matrices that satisfy this condition:
 * Condition = isOutput == true && passedFrustumCulling == true
 *
 * Basic Example:
 * Graph Configuration:
 *
 *    ---A---
 *   /  / \  \
 *  B  C   D  E
 *      \ /
 *       F
 *      /|\
 *     G H I
 *
 * Root: A
 * FrustumCulling is disabled on everynode
 * Nodes with isOutput==true: B G H I E
 * Output:
 * B0 = A * B
 * G0 = A * C * F * G
 * G1 = A * D * F * G
 * H0 = A * C * F * H
 * H1 = A * D * F * H
 * IO = A * D * F * I
 * I1 = A * D * F * I
 * E0 = A * E
 *
 * Matrices Buffer
 *
 *
 *
 *
 */
