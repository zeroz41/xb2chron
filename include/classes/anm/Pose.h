#ifndef CLASSES_ANM_POSE_H
#define CLASSES_ANM_POSE_H

#include "classes/anm/ReferenceObject.h"

namespace anm { class QsTransform; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B81158
class Pose : public ::anm::ReferenceObject {
public:
    // how a bone's model-space change reaches its children (setBoneModelSpace); no value has a name yet
    enum PROPAGATE_TYPE {};

    Pose(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    virtual ~Pose();  // slot 0
    const QsTransform& getBoneLocalSpace(unsigned short bone);
    const QsTransform& getBoneModelSpace(unsigned short bone);
    void setBoneLocalSpace(unsigned short bone, QsTransform const& transform);
    void setBoneModelSpace(unsigned short bone, QsTransform const& transform, PROPAGATE_TYPE propagate);
    void syncLocalSpace();
    void syncModelSpace();

    const Skeleton* m_pSkeleton;  // the constructor's; anm_pose.cpp asserts `m_pSkeleton`
    unsigned char pad_20[0x70];   // Factory::createPose allocates 0x90 bytes
};
}  // namespace anm

#endif
