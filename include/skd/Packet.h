#ifndef SKD_PACKET_H
#define SKD_PACKET_H

#include "anm/JobQueue.h"
#include "classes/anm/Pose.h"
#include "mm/MMStdBase.h"

// skdlib's skd_packet.h, as skdlib's own files' include path named it (the only spelling known)
#define SKD_PACKET_PATH "../../src\\skdlib/composite/skd_packet.h"

namespace anm { class Pose; }
namespace mm { namespace mtl { class IAllocator; }}
namespace skd { class ForceInterface; }

namespace skd {
// what a dynamics' solvers work from (1.0.0's DynamicsSolver::init, solve and resetNodes take one): the bind pose,
// the force, the job queue the detection jobs run on and the solve's iteration count. skd::Dynamics holds one at
// 0x48. The names other than m_pBindPose (skd_packet.h asserts it) are not the original's.
class Packet {
public:
    Packet(mm::mtl::IAllocator* allocator, anm::Pose& bindPose);
    ~Packet();

    // the pose the solvers start from, referenced (skd_packet.h asserts there was none)
    void setBindPose(anm::Pose& bindPose) {
#line 50 SKD_PACKET_PATH
        MM_ASSERT(m_pBindPose == nullptr);
        m_pBindPose = &bindPose;
        m_pBindPose->addRef();
    }

    anm::Pose* m_pBindPose;
    // 1.0.0's DynamicsSolver::solve calls its slot 0 with the step, the solver and its forces, when there is one
    ForceInterface* m_pForce;
    anm::JobQueue m_jobQueue;  // 128 jobs; the constructor registers the detection jobs' functions
    // how many times 1.0.0's DynamicsSolver::solve detects collisions and applies the constraints (6 from the
    // constructor; skd::Dynamics' header calls the same int m_level)
    int m_level;
};
}  // namespace skd

#endif
