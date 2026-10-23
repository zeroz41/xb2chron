#ifndef CLASSES_SKD_DYNAMICSSOLVER_H
#define CLASSES_SKD_DYNAMICSSOLVER_H

#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"
#include "skd/NodeArray.h"

namespace anm { class QsTransform; }
namespace anm { class ThreadPool; }
namespace mm { namespace mtl { class IAllocator; }}
namespace skd { class CollionArray; }
namespace skd { class Packet; }
namespace skd { class ResSolver; }

namespace skd {
// table 0x7100B81688; one solver of a dynamics: its resource's nodes simulated a step at a time
class DynamicsSolver {
public:
    DynamicsSolver(mm::mtl::IAllocator* allocator, const ResSolver& res, unsigned int index);
    virtual ~DynamicsSolver();  // slot 0
    virtual void solve(float deltaTime, const CollionArray& collisions, const Packet& packet);  // slot 2
    virtual void solveMT(float deltaTime, const CollionArray& collisions, const Packet& packet,
                         anm::ThreadPool& pool);  // slot 3
    void init(const Packet& packet);
    void convertCoordinateSystem(const anm::QsTransform& transform);
    void resetNodes(const Packet& packet);

    // the names below are not the original's
    const ResSolver* m_pRes;
    NodeArray m_nodes;
    float m_prevDeltaTime;               // the last step's deltaTime (1/30 at first), integrate's first argument
    mm::mtl::Vector<mm::Vec3> m_forces;  // per node, cleared and summed each step
    unsigned int m_index;                // the constructor's
    float m_blendWeight;                 // the nodes blend back by this much after a step when it is not 0
    bool m_initialized;                  // init's CalcUtil::initNodes succeeded: solve and solveMT do nothing before
};
}  // namespace skd

#endif
