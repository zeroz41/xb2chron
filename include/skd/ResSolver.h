#ifndef SKD_RESSOLVER_H
#define SKD_RESSOLVER_H

#include "anm/Array.h"

namespace skd { struct ResHingeConstraint; }
namespace skd { struct ResSpringConstraint; }
namespace skd { struct ResStickConstraint; }

namespace skd {
// one node of a solver resource (0x28 bytes, the stride anm::Array<ResNode> indexes with). Only what the detection
// jobs read is named, and the name is not the original's: bit 0 of m_flags set means the node takes no
// collision response (addDetectSphereJob gives it no DetectInfo).
struct ResNode {
    unsigned char pad_0[0x24];
    unsigned char m_flags;
    unsigned char pad_25[0x3];

    bool isFixed() const { return m_flags & 1; }
};

// a collision pair of a solver resource: the two nodes it moves, how the response is shared between them, the
// radius it detects with and the collision groups it tests (the names are not the original's: executeDetect*Job
// gives the first node (1 - m_weight) of the response and the second m_weight, and detects with m_radius;
// addDetect*Job tests bit `group` of m_groupMask)
struct ResNodeCollision {
    unsigned short m_node0;
    unsigned short m_node1;
    float m_weight;
    float m_radius;
    unsigned int m_groupMask;
};

// one solver of a dynamics resource: its nodes, collision pairs and constraints (DynamicsSolver's constructor and
// solve read these; the names are not the original's, the element types are 1.0.0's CalcUtil parameters)
class ResSolver {
public:
    unsigned char pad_0[0x8];
    anm::Array<ResNode> m_nodes;
    anm::Array<ResNodeCollision> m_collisions;
    anm::Array<ResStickConstraint> m_stickConstraints;
    anm::Array<ResSpringConstraint> m_springConstraints;
    anm::Array<ResHingeConstraint> m_hingeConstraints;
};
}  // namespace skd

#endif
