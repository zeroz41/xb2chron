#ifndef CLASSES_ANM_POSE_H
#define CLASSES_ANM_POSE_H

#include "classes/anm/ReferenceObject.h"
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/ReservedBitflag.h"
#include "mm/mtl/Vector.h"

namespace anm { class Skeleton; }
namespace mm { class Mat44; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B81158; a skeleton's bones' transforms, kept in local and in model space, each recomputed from the
// other when it is asked for (anm_pose.cpp)
class Pose : public ::anm::ReferenceObject {
public:
    // how a bone's model-space change reaches its children (setBoneModelSpace): 0 keeps the children's model
    // space (makeAllChildrenModelSpace), any other value their local space; no value has a name yet
    enum PROPAGATE_TYPE {};

    Pose(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    virtual ~Pose();  // slot 0
    const QsTransform& getBoneLocalSpace(unsigned short boneID);
    const QsTransform& getBoneModelSpace(unsigned short boneID);
    void setBoneLocalSpace(unsigned short boneID, QsTransform const& transform);
    void setBoneModelSpace(unsigned short boneID, QsTransform const& transform, PROPAGATE_TYPE propagate);
    // the bone's model-space transform to write in place (its children follow as setBoneModelSpace's do)
    QsTransform& accessBoneModelSpace(unsigned short boneID, PROPAGATE_TYPE propagate);
    void syncLocalSpace();
    void syncModelSpace();
    void setReferencePose();
    // the bone's model-space transform as a matrix, while the model space is synced
    void calcMatrixModelSpace(unsigned short boneID, mm::Mat44* pDst);
    // the transforms synced to the space they are written in, for a sampler to overwrite
    mm::mtl::Vector<QsTransform>& accessSyncedPoseLocalSpace();
    mm::mtl::Vector<QsTransform>& accessSyncedPoseModelSpace();

private:
    // the bone flags, a run of one flag per bone each (the assertions' names; the type's name and BONE_FLAG_2 are
    // not the original's: BONE_FLAG_2 marks the bones a model-space or local-space update walks through)
    enum BoneFlag {
        BONE_LOCAL_SPACE_DIRTY,
        BONE_MODEL_SPACE_DIRTY,
        BONE_FLAG_2,
    };
    // the pose's flags: every bone's local or model space up to date (the names are not the original's)
    enum PoseFlag {
        POSE_LOCAL_SPACE_SYNCED,
        POSE_MODEL_SPACE_SYNCED,
    };

    // the assertions' `testBoneFlag(boneID, ...)`
    bool testBoneFlag(unsigned short boneID, BoneFlag flag) const;
    void setBoneFlag(unsigned short boneID, BoneFlag flag, bool on);
    // the bone's model-space transform from its dirty ancestors' local ones
    const QsTransform& calcBoneModelSpace(unsigned short boneID);
    void makeAllChildrenLocalSpace(unsigned short boneID);
    void makeAllChildrenModelSpace(unsigned short boneID);

public:
    const Skeleton* m_pSkeleton;  // the constructor's; anm_pose.cpp asserts `m_pSkeleton`
    // per bone, its transform against its parent's (accessSyncedPoseLocalSpace; the name is not the original's)
    mm::mtl::Vector<QsTransform> m_localSpace;
    // per bone, its transform in the model (accessSyncedPoseModelSpace; the name is not the original's)
    mm::mtl::Vector<QsTransform> m_modelSpace;
    // three runs of a flag per bone, BoneFlag's (the name is not the original's)
    mm::mtl::ReservedBitflag m_boneFlags;
    mm::mtl::Bitflag<32> m_flags;  // PoseFlag's (the name is not the original's)
};
}  // namespace anm

#endif
