#ifndef SKD_DETECTJOB_H
#define SKD_DETECTJOB_H

#include "anm/JobQueue.h"
#include "mm/Vec3.h"

namespace skd { class DetectInfoBuffer; }
namespace skd { class NodeArray; }
namespace skd { class ShpereCollObj; }
namespace skd { struct DetectInfo; }
namespace skd { struct ResNodeCollision; }

namespace skd {
// a sphere's detection against one collision pair, run on a JobQueue (function 0): it writes the push into each
// node's DetectInfo, where there is one. 1.0.0 kept the constructor out of line; 3.0.1 has no copy.
struct DetectSphereJob : public anm::Job {
    DetectSphereJob(const ShpereCollObj* obj, const ResNodeCollision* collision, const mm::Vec3& pos,
                    DetectInfo* info0, DetectInfo* info1)
        : anm::Job(_TYPE_NAME, sizeof(DetectSphereJob), 0), m_pObj(obj), m_pCollision(collision), m_pos(pos),
          m_pInfo0(info0), m_pInfo1(info1) {}

    static const char* _TYPE_NAME;  // "DetectSphereJob"

    const ShpereCollObj* m_pObj;
    const ResNodeCollision* m_pCollision;
    mm::Vec3 m_pos;
    DetectInfo* m_pInfo0;
    DetectInfo* m_pInfo1;
};

void executeDetectSphereJob(anm::Job& job);
void addDetectSphereJob(const ShpereCollObj* obj, const ResNodeCollision* collision, const NodeArray* nodes,
                        const mm::Vec3& pos, DetectInfoBuffer* buffer, anm::JobQueue* queue);
}  // namespace skd

#endif
