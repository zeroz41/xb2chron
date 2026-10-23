#ifndef SKD_NODEARRAY_H
#define SKD_NODEARRAY_H

#include "anm/Array.h"
#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"
#include "skd/ResSolver.h"

namespace skd {
// a node a solver simulates (0xB0 bytes, Vector<Node>'s stride). Only the push the apply-detect jobs add to is
// named (executeApplyDetectJob adds the mean of its DetectInfos' pushes; the name is not the original's).
struct Node {
    unsigned char pad_0[0x50];
    mm::Vec3 m_push;
    unsigned char pad_60[0x50];
};

// a solver's nodes: its resource's nodes and collisions and the nodes it simulates (1.0.0's NodeArray::NodeArray
// builds them so; the names are not the original's)
class NodeArray {
public:
    NodeArray(mm::mtl::IAllocator* allocator, const anm::Array<ResNode>& resNodes,
              const anm::Array<ResNodeCollision>& resCollisions);

    const anm::Array<ResNode>* m_pResNodes;
    const anm::Array<ResNodeCollision>* m_pResCollisions;
    mm::mtl::Vector<Node> m_nodes;
};
}  // namespace skd

#endif
