#ifndef SKD_NODEARRAY_H
#define SKD_NODEARRAY_H

#include "anm/Array.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"
#include "skd/ResSolver.h"

namespace skd {
// a node a solver simulates (0xB0 bytes, Vector<Node>'s stride). The names are not the original's: CalcUtil's steps
// show what each holds. cacheNode takes the bone's model-space translation (m_animPos), its local translation
// (m_localPos) and the direction to its parent (m_dir, -unitY for a root); integrate moves m_pos on from m_prevPos
// and m_accel (applyAccel's force over the node's mass) into m_nextPos, or puts a fixed node's m_nextPos at
// m_animPos; the constraints and executeApplyDetectJob move m_nextPos; blendNode blends m_nextPos toward
// m_animPos; writeBackNode makes m_pos the old m_prevPos and m_nextPos the new m_pos, and keeps the parent bone's
// model-space translation and rotation (m_parentPos, m_parentRot).
struct Node {
    mm::Vec3 m_pos;
    mm::Quat m_rot;
    mm::Vec3 m_prevPos;
    mm::Vec3 m_parentPos;
    mm::Quat m_parentRot;
    mm::Vec3 m_nextPos;
    mm::Vec3 m_accel;
    mm::Vec3 m_animPos;
    mm::Vec3 m_localPos;
    mm::Vec3 m_dir;
    unsigned short m_bone;  // the pose's bone the node follows
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
