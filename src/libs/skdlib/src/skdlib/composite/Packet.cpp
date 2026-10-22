#include "mm/mtl/Queue.h"
#include "classes/anm/ReferenceObject.h"
#include "skd/Packet.h"
#include "skd/CalcUtil.h"
#include "skd/Solver.h"

namespace skd {

Packet::Packet(mm::mtl::IAllocator* allocator, anm::Pose& bindPose)
    : m_pBindPose(nullptr), m_pForce(nullptr), m_jobQueue(allocator, 128), m_level(6) {
    registerApplyDetectJobExecuter(&m_jobQueue);
    registerDetectCapsuleJobExecuter(&m_jobQueue);
    registerDetectPlaneJobExecuter(&m_jobQueue);
    registerDetectSphereJobExecuter(&m_jobQueue);
    setBindPose(bindPose);
}

Packet::~Packet() {
    if (m_pBindPose != nullptr) {
        m_pBindPose->release();
        m_pBindPose = nullptr;
    }
}

}  // namespace skd
