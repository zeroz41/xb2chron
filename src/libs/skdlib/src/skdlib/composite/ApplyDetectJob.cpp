#include "anm/Array.h"
#include "anm/JobQueue.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"
#include "skd/ResSolver.h"
#include "skd/NodeArray.h"
#include "skd/DetectInfo.h"
#include "skd/CalcUtil.h"
#include "skd/Solver.h"
#include "classes/skd/DynamicsSolver.h"
#include "classes/anm/ThreadPool.h"
#include "classes/fw/ForceCalculator.h"
#include "skd/Packet.h"

namespace skd {

const char* ApplyDetectJob::_TYPE_NAME = "ApplyDetectJob";

void executeApplyDetectJob(anm::Job& job) {
    ApplyDetectJob& applyJob = static_cast<ApplyDetectJob&>(job);
    mm::Vec3 push = mm::Vec3::zero;
    float count = 0.0f;
    for (DetectInfo** it = applyJob.m_infos.begin(); it != applyJob.m_infos.end(); ++it) {
        push += (*it)->m_push;
        count += 1.0f;
    }
    if (count > 1.1920928955078125e-07F) {
        mm::Vec3 mean = push * (1.0f / count);
        Node& node = applyJob.m_pNodes->m_nodes[applyJob.m_node];
        // by component: each sum loads the mean first, as mm::Vec3's operator+= does not
        node.m_push.x += mean.x;
        node.m_push.y += mean.y;
        node.m_push.z += mean.z;
    }
}

void registerApplyDetectJobExecuter(anm::JobQueue* queue) {
    queue->registerFunc(3, executeApplyDetectJob);
}

}  // namespace skd
