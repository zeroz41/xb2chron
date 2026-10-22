#ifndef CLASSES_ANM_POSE_H
#define CLASSES_ANM_POSE_H

namespace anm { class QsTransform; }
namespace anm { class Skeleton; }

namespace anm {
// table 0x7100B81158
class Pose {
public:
    // how a bone's model-space change reaches its children (setBoneModelSpace); no value has a name yet
    enum PROPAGATE_TYPE {};

    virtual ~Pose();  // slot 0
    const QsTransform& getBoneLocalSpace(unsigned short bone);
    const QsTransform& getBoneModelSpace(unsigned short bone);
    void setBoneLocalSpace(unsigned short bone, QsTransform const& transform);
    void setBoneModelSpace(unsigned short bone, QsTransform const& transform, PROPAGATE_TYPE propagate);

    unsigned char pad_8[0x10];
    const Skeleton* m_pSkeleton;  // the constructor's; anm_pose.cpp asserts `m_pSkeleton`
};
}  // namespace anm

#endif
