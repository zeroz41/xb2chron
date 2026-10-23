#ifndef SKD_SOLVER_H
#define SKD_SOLVER_H

#include "anm/JobQueue.h"
#include "mm/mtl/FixedVector.h"

namespace skd { class DetectInfoBuffer; }
namespace skd { class NodeArray; }
namespace skd { struct DetectInfo; }

namespace skd {
// one node's share of a solve's detections, run on a JobQueue (function 3): it adds the mean of the DetectInfos'
// pushes to the node (the names of the members are not the original's)
struct ApplyDetectJob : public anm::Job {
    ApplyDetectJob(unsigned short node, const mm::mtl::FixedVector<DetectInfo*, 32>& infos, NodeArray* nodes)
        : anm::Job(_TYPE_NAME, sizeof(ApplyDetectJob), 3), m_node(node), m_pNodes(nodes) {
        m_infos = infos;  // assigned (m_pNodes is stored before the copy)
    }

    static const char* _TYPE_NAME;  // "ApplyDetectJob"

    unsigned short m_node;
    mm::mtl::FixedVector<DetectInfo*, 32> m_infos;
    NodeArray* m_pNodes;
};

// skd_solver.cpp's: the function the queue runs its apply-detect jobs with, registered (skd::Packet's constructor)
void executeApplyDetectJob(anm::Job& job);
void registerApplyDetectJobExecuter(anm::JobQueue* queue);
void addApplyDetectJobs(DetectInfoBuffer& buffer, NodeArray* nodes, anm::JobQueue* queue);
}  // namespace skd

#endif
